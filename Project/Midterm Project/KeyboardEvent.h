#pragma once

#include <Trackable.h>
//#include <Event.h>
#include "InterfaceEvent.h"

enum KeyboardEventType
{
	KEYCODE_SPACE,
	KEYCODE_ESCAPE,
	KEYCODE_S,
	KEYCODE_F,
	KEYCODE_ENTER
};

class KeyboardEvent : public InterfaceEvent
{
public:

	KeyboardEvent(std::string key);
	virtual ~KeyboardEvent();

	inline string getKeyCode() const { return mKeyCode; };

private:

	std::string mKeyCode;
};
