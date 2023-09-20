#include "MouseEvent.h"

MouseEvent::MouseEvent(int button)
	:InterfaceEvent(COMPUTER_MOUSE_EVENT)
	, mButton(button)
{
}

MouseEvent::~MouseEvent()
{

}