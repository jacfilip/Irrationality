#pragma once
#include "GameScene.h"
#include "EventReceiver.h"
#include "ResourceManager.h"

#include <irrlicht.h>

#include <stdlib.h>
#include <vector>

using namespace std;
using namespace irr;

extern class GameScene;

enum WorkState
{
	FREE_CAMERA_FLOW = 0,
	GUI_MODE = 1
};

class WorkManager
{
public:
	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;

	EventReceiver* eventReceiver;
	ResourceManager resources;
private:
	vector<GameScene*> scenes;
	int activeScene;
	WorkState state;

	bool cursorLocked;

public:
	WorkManager(IrrlichtDevice* device, video::IVideoDriver* driver, scene::ISceneManager* smgr, EventReceiver* receiver);

	void Run();
	void ProcessEvents();
	void AlterWorkState(WorkState st);
	void LockCursor(bool lock);

	void CreateNewScene();
	GameScene* GetActiveScene();
};

