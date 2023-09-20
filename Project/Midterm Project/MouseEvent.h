#pragma once

#include <Trackable.h>
//#include <Event.h>
#include "InterfaceEvent.h"

class MouseEvent : public InterfaceEvent
{
public:

	MouseEvent(int button);
	virtual ~MouseEvent();

	inline int getButton() const { return mButton; };

private:

	int mButton;
};