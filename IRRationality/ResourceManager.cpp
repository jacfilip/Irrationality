#include "ResourceManager.h"
#include "WorkManager.h"


ResourceManager::ResourceManager(WorkManager* wm, scene::ISceneManager* scene, video::IVideoDriver* driver, IrrlichtDevice* dev)
	: wm(wm), scene(scene), driver(driver), dev(dev)
{

}