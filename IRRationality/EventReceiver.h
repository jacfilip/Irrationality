#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace irr::gui;

static struct KeyMap
{
	EKEY_CODE CAMERA_LEFT = KEY_KEY_A;
	EKEY_CODE CAMERA_RIGHT = KEY_KEY_D;
	EKEY_CODE CAMERA_FORWARD = KEY_KEY_W;
	EKEY_CODE CAMERA_BACK = KEY_KEY_S;
	EKEY_CODE CAMERA_UP = KEY_SPACE;
	EKEY_CODE CAMERA_DOWN = KEY_KEY_C;

	EKEY_CODE SELECTED_X_POS = KEY_NUMPAD6;
	EKEY_CODE SELECTED_X_NEG = KEY_NUMPAD4;
	EKEY_CODE SELECTED_Y_POS = KEY_NUMPAD7;
	EKEY_CODE SELECTED_Y_NEG = KEY_NUMPAD1;
	EKEY_CODE SELECTED_Z_POS = KEY_NUMPAD8;
	EKEY_CODE SELECTED_Z_NEG = KEY_NUMPAD2;

	EKEY_CODE SELECTED_Y_ZERO = KEY_NUMPAD5;

	EKEY_CODE TOGGLE_GUI = KEY_TAB;

}KeyMap;


class EventReceiver : public IEventReceiver
{
public:
	struct MouseState
	{
		core::position2di prevPosition;
		core::position2di position;
		bool LeftButtonDown;
		bool RightButtonDown;
		
		MouseState() : LeftButtonDown(false), RightButtonDown(false) 
		{
			position = prevPosition = core::vector2di(0, 0);
		}

		core::position2di shift() { return position - prevPosition; }
	} mouseState;

	struct GUIEvent
	{
		s32 id;
		gui::IGUIElement* caller;
		gui::EGUI_EVENT_TYPE type;
	} guiEvent;

	bool GUIeventAwait = false;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event);

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE key) const;

	virtual bool IsKeyUp(EKEY_CODE key) const;

	virtual bool IsKeyPressed(EKEY_CODE key) const;

	void ResetInput();

	EventReceiver();


private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool KeyWasDown[KEY_KEY_CODES_COUNT];
};

