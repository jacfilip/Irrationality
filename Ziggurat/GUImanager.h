#pragma once
#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace gui;

extern class GameScene;

enum GUIElements
{
	INSERT_WND = 1,
};

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

	IGUIWindow* insertWindow;

public:
	GUImanager(GameScene* gs);

	void SetCrosshair(Crosshairs type);
	
	void PopToolboxWindow();
	void PopInfoBox(const wchar_t* message);
	
	void CloseToolboxWindow();
};

