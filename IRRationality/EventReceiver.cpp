#include "EventReceiver.h"


bool EventReceiver::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	if (event.EventType == EET_GUI_EVENT)
	{
		guiEvent.id = event.GUIEvent.Caller->getID();
		guiEvent.caller = event.GUIEvent.Caller;
		guiEvent.type = event.GUIEvent.EventType;

		GUIeventAwait = true;
	}
	else
		GUIeventAwait = false;

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			mouseState.LeftButtonDown = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			mouseState.LeftButtonDown = false;
			break;

		case EMIE_RMOUSE_PRESSED_DOWN:
			mouseState.RightButtonDown = true;
			break;

		case EMIE_RMOUSE_LEFT_UP:
			mouseState.RightButtonDown = false;
			break;

		case EMIE_LMOUSE_DOUBLE_CLICK:
			break;

		case EMIE_MOUSE_WHEEL:
			event.MouseInput.Wheel;
			break;

		case EMIE_MOUSE_MOVED:
			mouseState.position.X = event.MouseInput.X;
			mouseState.position.Y = event.MouseInput.Y;
			break;

		default:
			break;
		}
	}

	return false;
}

// This is used to check whether a key is being held down
bool EventReceiver::IsKeyDown(EKEY_CODE key) const
{
	return KeyIsDown[key];
}

bool EventReceiver::IsKeyUp(EKEY_CODE key) const
{
	return !KeyIsDown[key] && KeyWasDown[key];
}

bool EventReceiver::IsKeyPressed(EKEY_CODE key) const
{
	return KeyIsDown[key] && !KeyWasDown[key];
}

void EventReceiver::ResetInput()
{
	mouseState.prevPosition.X = mouseState.position.X;
	mouseState.prevPosition.Y = mouseState.position.Y;

	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyWasDown[i] = KeyIsDown[i];
}

EventReceiver::EventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = KeyWasDown[i] = false;
}