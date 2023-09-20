#include "InputTranslator.h"
#include "Game.h"

InputTranslator::InputTranslator()
{
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->addListener((EventType)NUM_BASE_EVENT_TYPES, this);
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::handleEvent(const Event& theEvent)
{
	EventSystem* eventSystem = EventSystem::getInstance();

	const InterfaceEvent& interfaceEvent = static_cast<const InterfaceEvent&>(theEvent);


	//string keyCode = keyboardEvent.getKeyCode();

	Game* gameInstance = Game::getInstance();

	switch (interfaceEvent.getInterfaceEventType())
	{
	case KEYCODE_ESCAPE: //eventSystem->fireEvent(GameEvent(QUIT_GAME)); 
		if (gameInstance->getPausedGame())
		{
			gameInstance->quitGame();
		}
		else if (!gameInstance->getPausedGame())
		{
			gameInstance->freeze();
		}
		break;
	case KEYCODE_SPACE: //eventSystem->fireEvent(GameEvent(FREEZE));
		if (!gameInstance->getGameStarted())
		{
			gameInstance->startGame();
		}
		else if (gameInstance->getGameStarted())
		{
			gameInstance->freeze();
		}
		break;
	case KEYCODE_ENTER: //eventSystem->fireEvent(GameEvent(CHANGE_SPRITE));
		//gameInstance->changeSprite();
		break;
	case KEYCODE_S: //eventSystem->fireEvent(GameEvent(SLOW_DOWN));
		//gameInstance->slowDown();
		break;
	case KEYCODE_F: //eventSystem->fireEvent(GameEvent(SPEED_UP));
		//gameInstance->speedUp();
		break;
	case MOUSE_1: //eventSystem->fireEvent(GameEvent(ADD_UNIT));
		if (gameInstance->getGameStarted() && !gameInstance->getPausedGame())
		{
			gameInstance->changeSprite();
		}
		break;
	case MOUSE_2: //eventSystem->fireEvent(GameEvent(DELETE_UNIT));
		//gameInstance->deleteUnit();
		break;
	}
}
