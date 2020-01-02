#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace irr::gui;

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

