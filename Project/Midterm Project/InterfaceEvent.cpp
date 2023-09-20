#include "InterfaceEvent.h"

InterfaceEvent::InterfaceEvent(EventType type, InterfaceEventType interfaceType)
	:Event((EventType)type), mEventType(interfaceType)
{

}

InterfaceEvent::~InterfaceEvent()
{

}