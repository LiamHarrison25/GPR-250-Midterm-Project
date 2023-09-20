#include "InputSystem.h"

InputSystem::InputSystem() 
{
	mpEventSystem = EventSystem::getInstance();
	mpQueue = al_create_event_queue();
	al_register_event_source(mpQueue, al_get_keyboard_event_source());
	al_register_event_source(mpQueue, al_get_mouse_event_source());
}

InputSystem::~InputSystem() 
{
	cleanup();
}

void InputSystem::init() 
{

}

void InputSystem::cleanup() 
{
	//TODO: Event System is potentially causing a memory leak. 

	//mpEventSystem->cleanupInstance();
	//mpEventSystem->cleanup();
	//mpEventSystem = nullptr;

}

//Old version without events
bool InputSystem::getKeyState(std::string key) 
{

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);
	

	if (key == "ESCAPE" && al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE))
	{
		return true;
	}
	else if (key == "ENTER" && al_key_down(&keyboardState, ALLEGRO_KEY_ENTER))
	{
		return true;

	}
	else if (key == "S" && al_key_down(&keyboardState, ALLEGRO_KEY_S))
	{
		return true;
	}
	else if (key == "F" && al_key_down(&keyboardState, ALLEGRO_KEY_F))
	{
		return true;
	}
	else if (key == "Space" && al_key_down(&keyboardState, ALLEGRO_KEY_SPACE))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//Old version without events
bool InputSystem::getMouseState(std::string button) 
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	if (button == "1" && mouseState.buttons & 1)
	{
		return true;
	}
	if (button == "2" && mouseState.buttons & 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//new input with events
void InputSystem::getStateEvent()
{

	ALLEGRO_EVENT theEvent;

	while (al_get_next_event(mpQueue, &theEvent))
	{
		if (theEvent.type == ALLEGRO_EVENT_KEY_DOWN || theEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			switch (theEvent.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, KEYCODE_ESCAPE));
				break;
			case ALLEGRO_KEY_ENTER:
				mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, KEYCODE_ENTER));
				break;
			case ALLEGRO_KEY_S:
				mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, KEYCODE_S));
				break;
			case ALLEGRO_KEY_F:
				mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, KEYCODE_F));
				break;
			case ALLEGRO_KEY_SPACE:
				mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, KEYCODE_SPACE));
				break;
			}

			switch (theEvent.mouse.button)
			{
			case 1: mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, MOUSE_1));
				break;
			case 2: mpEventSystem->fireEvent(InterfaceEvent(NUM_BASE_EVENT_TYPES, MOUSE_2));
				break;
			}

		}
	}
}


Vector2D InputSystem::getMousePos()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	Vector2D mousePos(mouseState.x, mouseState.y);

	return mousePos;
}
