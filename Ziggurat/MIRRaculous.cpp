// Ziggurat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <irrlicht.h>
#include "driverChoice.h"

#include "WorkManager.h"

using namespace irr;

#define FULLHD_WIDE 2560, 1080
#define WINDOWED_MODE 640, 480
#define FULLSCREEN true

typedef const wchar_t* raw_str;

core::vector2di WindowResolution(FULLHD_WIDE);

int main()
{
	EventReceiver receiver;
	
	IrrlichtDevice* dev = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(WindowResolution.X, WindowResolution.Y), 32, FULLSCREEN, false,false, &receiver);
	
	if (dev == 0)
		return 1; // could not create driver.
	
	video::IVideoDriver* driver = dev->getVideoDriver();
	scene::ISceneManager* smgr = dev->getSceneManager();
	
	dev->getFileSystem()->addFileArchive("resources");
		
	WorkManager wm(dev, driver, smgr, &receiver);

	wm.Run();

	dev->drop();
}
