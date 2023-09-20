#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(std::string key)
	:InterfaceEvent(KEYBOARD_EVENT)
	, mKeyCode(key)
{
}

KeyboardEvent::~KeyboardEvent()
{

}
