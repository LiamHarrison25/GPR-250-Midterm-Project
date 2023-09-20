#pragma once

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "InputTranslator.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "Timer.h"
#include <Trackable.h>
#include "HUD.h"
#include "SoundManager.h"
#include <string>
#include <fstream>



class InputSystem; //forward declarations
class Vector2D;
class UnitManager;

class Game :public Trackable 
{
public:

	static Game* getInstance(); 
	static void createInstance();
	static void destroyInstance();
	

	void init();
	void cleanup();
	void doLoop();

	void drawFromGraphicsSystem(GraphicsBuffer *buffer, Vector2D location, Sprite *sprite, float scale);
	void drawFromGraphicsSystem(Vector2D location, Sprite *sprite, float scale);
	GraphicsSystem* getGraphicsSystem();

	bool getPausedGame();
	bool getGameStarted();

	//Game Functions:
	void quitGame();
	void deleteUnit();
	void addUnit();
	void freeze();
	void changeSprite();
	void slowDown();
	void speedUp();
	void createRandomUnit();
	void readDataFromFile();
	void startGame();
	void endGame();

private:

	Game();
	~Game();

	static Game* mpsGame;
	
	//Consts for names/paths
	const std::string LOOP_TRACKER_NAME = "loop";
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string AUDIO_ASSET_PATH = "..\\..\\shared\\assets\\minetrap\\";
	const std::string WOODS_FILE_NAME = "woods.png";
	const std::string SMURF_FILE_NAME = "smurf_sprites.png";
	const std::string DEAN_FILE_NAME = "dean_sprites.png";
	const std::string ORB_FILE_NAME = "glowing-balls.png";
	const std::string DATA_INPUT_FILE = "data.txt";
	const std::string FONT_FILENAME = "cour.ttf";
	const std::string TIME_STRING = "Time: ";
	const std::string FPS_STRING = "FPS: ";
	const std::string SCORE_STRING = "Score: ";
	const std::string PAUSED_STRING = "Game Paused";
	const std::string START_STRING = "Press space bar to start";
	const std::string END_STRING = "Game Over. Press escape to quit";

	//Consts for other values
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const int FONT_SIZE = 24;
	const int SPAWN_DELAY_IN_SECONDS = 5;
	const int STARTING_SCORE = 10;
	const std::string AUDIO_SOURCE_1 = "1";
	const std::string AUDIO_SOURCE_2 = "2";
	const std::string AUDIO_SOURCE_3 = "3";
	const float TARGET_TIME = 16.7;

	void createInitialBuffers();
	void createSmurfUnit();
	void getInput(); //old version without events
	void update(float targetTimePerFrame);
	void render();

	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;
	InputTranslator* mpInputTranslator;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGraphicsBufferManager;
	Sprite mBackgroundSprite;
	HUD mHud;
	SoundManager mSoundManager;

	bool mContinueGame;
	bool mPausedGame;
	bool mGameStillRunning;
	bool mGameStarted;

	float mTimeInSeconds;
	float mFPS;
	int mScore;
	int mPreviousSecond;

	//Data Driven members
	float mVelocityMax;
	float mVelocityMin;
	float mSpeedMax;
	float mSpeedMin;
	std::string mAudio1;
	std::string mAudio2;
	std::string mAudio3;
	int mPointsAddition;
	int mPointsSubtraction;
	
};
