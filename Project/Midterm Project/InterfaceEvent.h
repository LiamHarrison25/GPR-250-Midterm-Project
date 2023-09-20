#pragma once

#include "Trackable.h"
#include <Event.h>

enum InterfaceEventType
{
	KEYCODE_SPACE = 1,
	KEYCODE_ESCAPE,
	KEYCODE_S,
	KEYCODE_F,
	KEYCODE_ENTER,
	MOUSE_1,
	MOUSE_2,
};

class InterfaceEvent :public Event
{
public:
	InterfaceEvent(EventType type, InterfaceEventType interfaceType);
	virtual ~InterfaceEvent();

	InterfaceEventType getInterfaceEventType() const { return mEventType; }

private:

	InterfaceEventType mEventType;

};
