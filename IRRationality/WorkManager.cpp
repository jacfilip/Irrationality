#include <irrlicht.h>

#include "WorkManager.h"
#include "GUImanager.h"

extern core::position2di WindowResolution;

WorkManager::WorkManager(IrrlichtDevice* device, video::IVideoDriver* driver, scene::ISceneManager* smgr, EventReceiver* receiver)
	: resources(this, smgr, driver, device), updateFPS(120.f)
{
	this->device = device;
	this->driver = driver;
	this->smgr = smgr;
	this->eventReceiver = receiver;

	this->cursorLocked = false;

	this->device->getCursorControl()->setPosition(core::position2di(WindowResolution.X / 2, WindowResolution.Y / 2));
	this->eventReceiver->mouseState.position =
		this->eventReceiver->mouseState.prevPosition = core::position2di(WindowResolution.X / 2, WindowResolution.Y / 2);

	CreateNewScene();
	activeScene = 0;

	AlterWorkState(WorkState::FREE_CAMERA_FLOW);

	scenes[activeScene]->objFactory->AddCube(vector3df(0, 0, 0))->ApplyTexture(L"wooden_crate.jpg", 0);
	scenes[activeScene]->objFactory->AddCube(vector3df(20, 0, 0))->ApplyTexture(L"wooden_crate.jpg", 0);
	scenes[activeScene]->objFactory->AddCube(vector3df(40, 0, 0))->ApplyTexture(L"wooden_crate.jpg", 0);
	scenes[activeScene]->objFactory->AddSprite(vector3df(60, 0, 0), driver->getTexture(L"wooden_crate.jpg"));

	scenes[activeScene]->objFactory->AddPoly(std::vector<vector3df> 
	{	vector3df(0, 0, 0), 
		vector3df(100, 0, 0), 
		vector3df(0, 0, 100), 
		vector3df(10, 50, 110)}, driver->getTexture(L"wooden_crate.jpg"),
		scene::EPT_TRIANGLE_STRIP)->ApplyTexture(L"wooden_crate.jpg", 0);
}

void WorkManager::Run()
{
	while (device->run())
	{
		//Quit app
		if (eventReceiver->IsKeyDown(EKEY_CODE::KEY_LCONTROL) && eventReceiver->IsKeyPressed(EKEY_CODE::KEY_KEY_Q))
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
		scenes[activeScene]->GUI->SetCrosshair(Crosshairs::CROSS);
		scenes[activeScene]->GUI->CloseToolboxWindow();
		scenes[activeScene]->GUI->CloseObjectPropertiesWindow();
		scenes[activeScene]->GUI->CloseToolbar();
		break;
	case GUI_MODE:
		LockCursor(false);
		scenes[activeScene]->GUI->SetCrosshair(Crosshairs::POINTER);
		scenes[activeScene]->GUI->PopToolboxWindow();
		scenes[activeScene]->GUI->PopObjectPropertyWindow();
		scenes[activeScene]->GUI->PopToolbar();
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
		scenes[activeScene]->UpdateScene(device->getTimer()->getTime());
		scenes[activeScene]->DrawScene();

		if (eventReceiver->IsKeyPressed(KEY_TAB))
			AlterWorkState(WorkState::GUI_MODE);
		else if (eventReceiver->IsKeyPressed(EKEY_CODE::KEY_ESCAPE))
			scenes[activeScene]->DeselectObject();
		else if (eventReceiver->IsKeyDown(EKEY_CODE::KEY_DELETE) && scenes[activeScene]->selectedObject)
		{
			scenes[activeScene]->selectedObject->Destroy();
			scenes[activeScene]->GUI->RefreshToolBoxWindow();
			//LockCursor(true);
			//device->getGUIEnvironment()->addMessageBox(L"Removing object.", L"Are you sure you want to remove this object?", true, EMBF_YES | EMBF_NO, 0, OBJ_PROPERTY_BOX_REMOVE_CONFIRM);
			//LockCursor(false);
		}
	
		break;
	case WorkState::GUI_MODE:
		if (eventReceiver->IsKeyPressed(KeyMap.TOGGLE_GUI))
			AlterWorkState(WorkState::FREE_CAMERA_FLOW);
		scenes[activeScene]->DrawScene();
		break;
	default:
		break;
	}

	if (this->eventReceiver->GUIeventAwait)
		scenes[activeScene]->HandleGUIEvents(this->eventReceiver->guiEvent);
}

void WorkManager::CreateNewScene()
{
	scenes.push_back(new GameScene(this));
	LockCursor(true);
}

GameScene* WorkManager::GetActiveScene()
{
	return scenes[activeScene];
}
