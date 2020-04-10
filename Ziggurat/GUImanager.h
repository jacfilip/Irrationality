#pragma once
#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace gui;

extern class GameScene;

enum GUIElements
{
	INSERT_WND = 1,
	OBJ_ADD_COMBO_BOX = 2,
	OBJ_PROPERTY_BOX = 3,
	OBJ_PROPERTY_BOX_POS_X = 4,
	OBJ_PROPERTY_BOX_POS_Y = 5,
	OBJ_PROPERTY_BOX_POS_Z = 6,
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

	IGUIWindow* toolboxWindow;
	IGUIWindow* propertiesWindow;

	IGUIComboBox* objAddComboBox;

public:
	GUImanager(GameScene* gs);

	void SetCrosshair(Crosshairs type);
	
	void PopToolboxWindow();
	void PopInfoBox(const wchar_t* message);
	void PopObjectPropertyWindow();

	void CloseToolboxWindow();
	void CloseObjectPropertiesWindow();
};

