#include "Game.h"
#include "GameEvent.h"
#include <vector>
#include "Animation.h"
#include "Unit.h"
#include "Color.h"

Game* Game::mpsGame = nullptr;

Game::Game() 
{
	mContinueGame = true;
	mpGraphicsBufferManager = nullptr;
	mpGraphicsSystem = nullptr;
	mpInputSystem = nullptr;
	mpUnitManager = nullptr;
	mpInputTranslator = nullptr;

	//EventSystem* eventSystem = EventSystem::getInstance();
	//eventSystem->addListener((EventType)NUM_BASE_EVENT_TYPES, this);

	mScore = STARTING_SCORE;
	mFPS = 0;
	mTimeInSeconds = 0;
	mPreviousSecond = 0;
	mPausedGame = true;
	mGameStarted = false;
	mGameStillRunning = true;

	//Data driven members
	mVelocityMax = 0;
	mVelocityMin = 0;
	mSpeedMax = 0;
	mSpeedMin = 0;
	mAudio1 = "";
	mAudio2 = "";
	mAudio3 = "";
	mPointsAddition = 0;
	mPointsSubtraction = 0;
}

Game::~Game()
{
	cleanup();
}

Game* Game::getInstance()
{
	assert(mpsGame);
	return mpsGame;
}

void Game::createInstance()
{

	if (mpsGame == nullptr)
	{
		mpsGame = new Game;
	}

}

void Game::destroyInstance()
{
	delete mpsGame;
	mpsGame = nullptr;
}


void Game::init()
{
	mpGraphicsSystem = new GraphicsSystem; //creates the graphics system
	mpInputSystem = new InputSystem;
	mpGraphicsBufferManager = new GraphicsBufferManager;
	mpInputTranslator = new InputTranslator;

	createInitialBuffers();

	mBackgroundSprite = Sprite(Vector2D(0, 0), DISP_HEIGHT, DISP_WIDTH, mpGraphicsBufferManager->getGraphicsBuffer("BLACK_BUFFER"));

	mpGraphicsSystem->draw(Vector2D(0, 0), &mBackgroundSprite, 1.0f); //draws the woods sprite to the backbuffer

	mpUnitManager = new UnitManager(10000);

	Font font(al_load_ttf_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, 0), FONT_SIZE);

	mHud.addFont(font);

	readDataFromFile();

	ALLEGRO_SAMPLE* audioSample1 = al_load_sample((AUDIO_ASSET_PATH + mAudio1).c_str());
	ALLEGRO_SAMPLE* audioSample2 = al_load_sample((AUDIO_ASSET_PATH + mAudio2).c_str());
	ALLEGRO_SAMPLE* audioSample3 = al_load_sample((AUDIO_ASSET_PATH + mAudio3).c_str());

	mSoundManager.addSample(audioSample1, AUDIO_SOURCE_1);
	mSoundManager.addSample(audioSample2, AUDIO_SOURCE_2);
	mSoundManager.addSample(audioSample3, AUDIO_SOURCE_3);

	srand((unsigned int)time(NULL));

}

void Game::createInitialBuffers()
{
	//GraphicsBuffer* woodBuffer = new GraphicsBuffer((ASSET_PATH + WOODS_FILE_NAME).c_str());
	//mpGraphicsBufferManager->addGraphicsBuffer(woodBuffer, WOODS_FILE_NAME);

	int blackColor[4] = { 0, 0, 0, 255 };
	Color color(blackColor);

	GraphicsBuffer* blackBuffer = new GraphicsBuffer(DISP_WIDTH, DISP_HEIGHT);
	blackBuffer->setBitmapToColor(al_map_rgba(color.getColor(0), color.getColor(1), color.getColor(2), color.getColor(3)));
	mpGraphicsBufferManager->addGraphicsBuffer(blackBuffer, "BLACK_BUFFER");

	GraphicsBuffer* orbBuffer = new GraphicsBuffer((ASSET_PATH + ORB_FILE_NAME).c_str());
	mpGraphicsBufferManager->addGraphicsBuffer(orbBuffer, ORB_FILE_NAME);

	GraphicsBuffer* smurfBuffer = new GraphicsBuffer((ASSET_PATH + SMURF_FILE_NAME).c_str());
	mpGraphicsBufferManager->addGraphicsBuffer(smurfBuffer, SMURF_FILE_NAME);

	GraphicsBuffer* deanBuffer = new GraphicsBuffer((ASSET_PATH + DEAN_FILE_NAME).c_str());
	mpGraphicsBufferManager->addGraphicsBuffer(deanBuffer, DEAN_FILE_NAME);
}

void Game::createSmurfUnit()
{
	Unit* unit = new Unit;
	unit->setAnimation(mpGraphicsBufferManager->getGraphicsBuffer(SMURF_FILE_NAME), mpGraphicsBufferManager->getGraphicsBuffer(DEAN_FILE_NAME));
	//mpUnitManager->addUnit(unit);
	//mpUniManager->addUnit()
}

void Game::cleanup() 
{
	//clean up all of the dynamic memory
	
	delete mpInputSystem;
	mpInputSystem = nullptr;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;

	delete mpUnitManager;
	mpUnitManager = nullptr;

	delete mpInputTranslator;
	mpInputTranslator = nullptr;

	delete mpGraphicsSystem; 
	mpGraphicsSystem = nullptr;
}

//Old input system without events
void Game::getInput() 
{
	//Get user input
	if (mpInputSystem->getKeyState("ESCAPE"))
	{
		
		if (mPausedGame)
		{
			quitGame();
		}
		else if(!mPausedGame)
		{
			freeze();
		}
	}

	if (mpInputSystem->getKeyState("ENTER"))
	{
		//changeSprite();
	}

	if (mpInputSystem->getKeyState("S"))
	{
		//slowDown();
	}

	if (mpInputSystem->getKeyState("F"))
	{
		//speedUp();
	}

	if (mpInputSystem->getKeyState("Space"))
	{
		
		if (!mGameStarted)
		{
			startGame();
		}
		else if(mGameStarted)
		{
			freeze();
		}
	}

	if (mpInputSystem->getMouseState("1"))
	{
		changeSprite();
		
	}

	if (mpInputSystem->getMouseState("2"))
	{
		//deleteUnit();
	}
}

void Game::update(float targetTimePerFrame) 
{
	mpUnitManager->update(targetTimePerFrame);
	int size = mpUnitManager->getListSize();
	int i;
	for (i = 0; i < size; i++)
	{
		Unit* theUnit = mpUnitManager->getUnit(i);
		if (theUnit->shouldBeDead())
		{
			if (theUnit->getIsRed())
			{
				mSoundManager.playSample(AUDIO_SOURCE_2, false);
				mScore-= mPointsSubtraction;
			}
			else
			{
				mSoundManager.playSample(AUDIO_SOURCE_1, false);
				mScore+= mPointsAddition;
			}
			mpUnitManager->deleteUnit(i); 
			createRandomUnit();
		}
	}

	if (mScore <= 0)
	{
		endGame(); //ends the game
	}

	//spawns in a new unit every (SPAWN_DELAY_IN_SECONDS) seconds
	if (mPreviousSecond < (int)mTimeInSeconds)
	{
		mPreviousSecond = (int)mTimeInSeconds;

		if ((int)mTimeInSeconds % SPAWN_DELAY_IN_SECONDS == 0) 
		{
			createRandomUnit();
		}
	}

}

void Game::render() 
{
	//Draw current game state

	mpGraphicsSystem->draw(Vector2D(0, 0), &mBackgroundSprite, 1.0f);

	//draw smurf sprite to backbuffer
	if (mGameStillRunning)
	{
		mpUnitManager->draw();
	}

	//Render the HUD
	std::string timeInString = TIME_STRING + to_string(int(mTimeInSeconds));
	mHud.writeText(timeInString, Vector2D(60, 100)); 

	std::string fpsInString = FPS_STRING + to_string(int(mFPS));
	mHud.writeText(fpsInString, Vector2D(60, 50));

	std::string scoreInString = SCORE_STRING + to_string(mScore);
	mHud.writeText(scoreInString, Vector2D(60, 0));

	if (mPausedGame && mGameStarted && mGameStillRunning)
	{
		mHud.writeText(PAUSED_STRING, Vector2D(mpGraphicsSystem->getWidth() / 2.0f, mpGraphicsSystem->getHeight() / 2.0f));
	}

	if (!mGameStarted)
	{
		mHud.writeText(START_STRING, Vector2D(mpGraphicsSystem->getWidth() / 2.0f, mpGraphicsSystem->getHeight() / 2.0f));
	}

	if (!mGameStillRunning)
	{
		mHud.writeText(END_STRING, Vector2D(mpGraphicsSystem->getWidth() / 2.0f, mpGraphicsSystem->getHeight() / 2.0f));
	}

	//flip the backbuffer
	mpGraphicsSystem->flip();
}

void Game::doLoop() 
{
	PerformanceTracker* performanceTracker = new PerformanceTracker;
	mContinueGame = true;
	Timer timer;

	bool gameStarted = false;

	createRandomUnit();
	
	while (mContinueGame)
	{
		
		performanceTracker->clearTracker(LOOP_TRACKER_NAME);
		performanceTracker->startTracking(LOOP_TRACKER_NAME);
		timer.start();
			
		//Get user input
		//getInput();

		mpInputSystem->getStateEvent();

		if (!mPausedGame && mGameStarted)
		{
			update(TARGET_TIME);
		}

		render();

		//flip the backbuffer
		mpGraphicsSystem->flip(); 
		
		//wait until the target amount of time has elapsed

		timer.sleepUntilElapsed(TARGET_TIME);

		performanceTracker->stopTracking(LOOP_TRACKER_NAME);
		if (!mPausedGame)
		{
			mTimeInSeconds += performanceTracker->getElapsedTime(LOOP_TRACKER_NAME) / 1000;
		}

		mFPS = 1000 / performanceTracker->getElapsedTime(LOOP_TRACKER_NAME);
		

		std::cout << performanceTracker->getElapsedTime(LOOP_TRACKER_NAME) << std::endl;		
		
	}
	
}

void Game::drawFromGraphicsSystem(Vector2D location, Sprite *sprite, float scale)
{
	mpGraphicsSystem->draw(location, sprite, scale);
}

void Game::drawFromGraphicsSystem(GraphicsBuffer *buffer, Vector2D location, Sprite *sprite, float scale)
{
	mpGraphicsSystem->draw(buffer, location, sprite, scale);
}

GraphicsSystem* Game::getGraphicsSystem()
{
	return mpGraphicsSystem;
}

void Game::quitGame()
{
	//Quit the game
	mContinueGame = false;
}

void Game::deleteUnit()
{
	//delete the unit
	int size = mpUnitManager->getListSize();
	int i;
	Vector2D mousePos = mpInputSystem->getMousePos();
	for (i = 0; i < size; i++)
	{
		Unit* unit = mpUnitManager->getUnit(i);
		Vector2D location = unit->getLocation();

		if (mousePos.getX() >= location.getX() && mousePos.getX() <= location.getX() + 32)
		{
			if (mousePos.getY() >= location.getY() && mousePos.getY() <= location.getY() + 32)
			{
				//Destroy the Unit
				mpUnitManager->deleteUnit(i);
				break;
			}
		}

	}
}

void Game::addUnit()
{
	//add a new unit
	Vector2D mousePos = mpInputSystem->getMousePos();

	createSmurfUnit();
	int unitIndex = mpUnitManager->getListSize() - 1;

	//place unit at mousePos
	mpUnitManager->getUnit(unitIndex)->setLocation(mousePos);
}

void Game::freeze()
{
	//Freeze all of the Units
	mpUnitManager->freezeAllUnits();
	mPausedGame = !mPausedGame;
}

void Game::changeSprite()
{

	int i, size = mpUnitManager->getListSize();

	Vector2D mousePos = mpInputSystem->getMousePos();
	for (i = 0; i < size; i++)
	{
		Unit* unit = mpUnitManager->getUnit(i);
		Vector2D location = unit->getLocation();

		if (mousePos.getX() >= location.getX() && mousePos.getX() <= location.getX() + 32)
		{
			if (mousePos.getY() >= location.getY() && mousePos.getY() <= location.getY() + 32)
			{
				//Change the sprite of the unit
				mSoundManager.playSample(AUDIO_SOURCE_3, false);
				//Change the sprite of the smurf
				if (mpUnitManager->getListSize() >= 1)
				{
					//int lastUnit = mpUnitManager->getListSize() - 1;
					Unit* theUnit = mpUnitManager->getUnit(i);
					theUnit->changeAnimation();
					bool theBool = theUnit->getIsRed();
					theUnit->setIsRed(!theBool);
				}
				break;
			}
		}

	}
}

void Game::slowDown()
{
	//Slow down the animation
	int size = mpUnitManager->getListSize();
	int i;
	for (i = 0; i < size; i++)
	{
		mpUnitManager->getUnit(i)->slowDownAnimation();
	}
}

void Game::speedUp()
{
	//Speed up the animation
	int size = mpUnitManager->getListSize();
	int i;
	for (i = 0; i < size; i++)
	{
		mpUnitManager->getUnit(i)->speedUpAnimation();
	}
}

void Game::createRandomUnit()
{
	int width = mpGraphicsSystem->getWidth();
	int height = mpGraphicsSystem->getHeight();

	//srand((unsigned int)time(NULL));
	int velocityRange = (mVelocityMax - mVelocityMin) + 1;

	int x = rand() % velocityRange + mVelocityMin;
	int y = rand() % velocityRange + mVelocityMin;
	Vector2D velocity(x, y);

	int speedRange = (mSpeedMax - mSpeedMin) + 1;
	int speed = rand() % speedRange + mSpeedMin;

	float accel = 0;

	Animation* orbAnimation = new Animation;

	//Unit* newUnit = new Unit(orbAnimation, Vector2D(width / 2.0f, height / 2.0f), velocity, accel, speed); //old way without memory pool
	//newUnit->setAnimation(mpGraphicsBufferManager->getGraphicsBuffer(ORB_FILE_NAME), mpGraphicsBufferManager->getGraphicsBuffer(ORB_FILE_NAME)); //old way without memory pool
	mpUnitManager->addUnit(orbAnimation, Vector2D(width / 2.0f, height / 2.0f), velocity, accel, speed);
	mpUnitManager->getUnit(mpUnitManager->getListSize() - 1)->setAnimation(mpGraphicsBufferManager->getGraphicsBuffer(ORB_FILE_NAME), mpGraphicsBufferManager->getGraphicsBuffer(ORB_FILE_NAME));

}

void Game::readDataFromFile()
{

	ifstream inFile(DATA_INPUT_FILE);
	if (inFile.good())
	{
		inFile >> mVelocityMax;
		inFile >> mVelocityMin;
		inFile >> mSpeedMax;
		inFile >> mSpeedMin;
		inFile >> mAudio1;
		inFile >> mAudio2;
		inFile >> mAudio3;
		inFile >> mPointsAddition;
		inFile >> mPointsSubtraction;
	}

	inFile.close();

}

void Game::startGame() 
{
	//start the game
	mGameStarted = true;
	mPausedGame = false;
	
}

void Game::endGame() 
{
	//End the game
	mGameStillRunning = false;
	mPausedGame = true;
}

bool Game::getPausedGame()
{
	return mPausedGame;
}

bool Game::getGameStarted()
{
	return mGameStarted;
}
