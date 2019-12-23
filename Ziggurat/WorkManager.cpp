#include <irrlicht.h>

#include "WorkManager.h"
#include "GUImanager.h"

extern core::position2di WindowResolution;

WorkManager::WorkManager(IrrlichtDevice* device, video::IVideoDriver* driver, scene::ISceneManager* smgr, EventReceiver* receiver)
	: resources(this, smgr, driver, device)
{
	this->device = device;
	this->driver = driver;
	this->smgr = smgr;
	this->eventReceiver = receiver;

	this->cursorLocked = false;

	this->device->getCursorControl()->setPosition(core::position2di(WindowResolution.X / 2, WindowResolution.Y / 2));
	this->eventReceiver->mouseState.position =
		this->eventReceiver->mouseState.prevPosition = core::position2di(WindowResolution.X / 2, WindowResolution.Y / 2);

	CreateNewSecne();
	activeScene = 0;
}

void WorkManager::Run()
{
	while (device->run())
	{
		if (eventReceiver->IsKeyPressed(EKEY_CODE::KEY_ESCAPE))
			device->closeDevice();
		
		ProcessEvents();
		
		//set offset for window border (5px) to prevent 'floating'
		float offX = device->isFullscreen() ? 0 : 5;
		float offY = offX;
		
		if (cursorLocked)
		{
			device->getCursorControl()->setPosition(core::vector2di(WindowResolution.X / 2 + offX, WindowResolution.Y / 2 + offY));
			eventReceiver->mouseState.position = core::position2di(WindowResolution.X / 2, WindowResolution.Y / 2);
		}
		eventReceiver->ResetInput();
	}
}

void WorkManager::AlterWorkState(WorkState st)
{
	state = st;

	switch (state)
	{
	case FREE_CAMERA_FLOW:
		LockCursor(true);
		scenes[activeScene]->GUI->CloseInsertWindow();
		break;
	case CAMERA_FROZEN:
		LockCursor(false);
		scenes[activeScene]->GUI->SetCrosshair(Crosshairs::CROSS);
		scenes[activeScene]->GUI->PopInsertWindow();
		break;
	default:
		break;
	}
}

void WorkManager::LockCursor(bool lock)
{
	cursorLocked = lock;
	//device->getCursorControl()->setVisible(!lock);
}

void WorkManager::ProcessEvents()
{
	switch (state)
	{
	case WorkState::FREE_CAMERA_FLOW:
		scenes[activeScene]->MoveCamera();
		scenes[activeScene]->UpdateScene();
		scenes[activeScene]->DrawScene();
		if (eventReceiver->IsKeyPressed(KEY_TAB))
			AlterWorkState(WorkState::CAMERA_FROZEN);
		break;
	case WorkState::CAMERA_FROZEN:
		if (eventReceiver->IsKeyPressed(KEY_TAB))
			AlterWorkState(WorkState::FREE_CAMERA_FLOW);
		scenes[activeScene]->DrawScene();
		break;
	default:
		break;
	}

	if (this->eventReceiver->GUIeventAwait)
		scenes[activeScene]->HandleGUIEvents(this->eventReceiver->guiEvent);
}

void WorkManager::CreateNewSecne()
{
	scenes.push_back(new GameScene(this));
	LockCursor(true);
}