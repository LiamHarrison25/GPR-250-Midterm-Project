#pragma once

#include <Trackable.h>
#include "GameEvent.h"

class QuitGameEvent : public GameEvent
{
public:

	QuitGameEvent();
	virtual ~QuitGameEvent();

private:

};