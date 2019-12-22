#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace irr::gui;

extern class WorkManager;

class ResourceManager
{
private:
	WorkManager* wm;

	scene::ISceneManager* scene;
	video::IVideoDriver* driver;
	IrrlichtDevice* dev;

public:
	IGUISpriteBank* sprites;

	ResourceManager(WorkManager* wm, scene::ISceneManager* scene, video::IVideoDriver* driver, IrrlichtDevice* dev);
};

