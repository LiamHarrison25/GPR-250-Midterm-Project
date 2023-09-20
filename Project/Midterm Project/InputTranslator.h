#pragma once
#include <Trackable.h>
#include <EventListener.h>
#include <Event.h>
#include <EventSystem.h>
#include "InterfaceEvent.h"

//#include "GameEvent.h"
//#include "KeyboardEvent.h"
//#include "MouseEvent.h"
class Game;

class InputTranslator : public EventListener
{
public:

	void handleEvent(const Event& theEvent);

	InputTranslator();
	~InputTranslator();

private:


};
