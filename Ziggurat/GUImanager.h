#pragma once
#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace gui;

extern class GameScene;

enum Crosshairs
{
	NONE,
	CROSS,
	POINTER
};

class GUImanager
{
private:
	GameScene* scene;
	std::vector<IGUIElement*> guiElements;

	Crosshairs crosshairType;

public:
	GUImanager(GameScene* gs);

	void SetCrosshair(Crosshairs type);
};

