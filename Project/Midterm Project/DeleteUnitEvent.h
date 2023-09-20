#pragma once

#include <Trackable.h>
#include "GameEvent.h"

class DeleteUnitEvent : public GameEvent
{
public:

	DeleteUnitEvent();
	virtual ~DeleteUnitEvent();

private:

};
