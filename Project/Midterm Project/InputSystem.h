#pragma once

//#include "Game.h"
#include "InputSystem.h"
#include <Trackable.h>
#include <Vector2D.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <Event.h>
#include <EventSystem.h>

//#include "MouseEvent.h"
//#include "KeyboardEvent.h"
#include "FreezeEvent.h"
#include "AddUnitEvent.h"
#include "DeleteUnitEvent.h"
#include "QuitGameEvent.h"
#include "GameEvent.h"
#include "InterfaceEvent.h"

struct ALLEGRO_KEYBOARD_STATE;
struct ALLEGRO_MOUSE_STATE;

class InputSystem :public Trackable
{
public:

	InputSystem();
	~InputSystem();

	void init();
	void cleanup();

	bool getKeyState(std::string key); 
	bool getMouseState(std::string key); 

	void getStateEvent();

	Vector2D getMousePos();

private:

	EventSystem* mpEventSystem;
	ALLEGRO_EVENT_QUEUE* mpQueue;
	
};
