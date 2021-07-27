#pragma once
#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace gui;

extern class GameScene;

enum GUIElements
{
	INSERT_WND,
	OBJ_ADD_COMBO_BOX ,
	
	MENUSTRIP,
	MENUSTRIP_FILE,
	MENUSTRIP_FILE_EXIT,
	
	OBJ_PROPERTY_BOX,
	OBJ_PROPERTY_BOX_POS_X,
	OBJ_PROPERTY_BOX_POS_Y,
	OBJ_PROPERTY_BOX_POS_Z,
	OBJ_PROPERTY_BOX_ROT_X,
	OBJ_PROPERTY_BOX_ROT_Y,
	OBJ_PROPERTY_BOX_ROT_Z,
	OBJ_PROPERTY_BOX_REMOVE,
	OBJ_PROPERTY_BOX_REMOVE_CONFIRM,
	
	OBJ_PROPERTY_BOX_TEXTURE_SET,
	OBJ_PROPERTY_BOX_TEXTURE_OPEN_FILE_DIALOG,
	OBJ_PROPERTY_BOX_TEXTURE_NAME,

	TOOL_BOX_OBJ_LIST,
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
	IGUIListBox* objectList;
	IGUIContextMenu* menu;

public:
	GUImanager(GameScene* gs);

	void SetCrosshair(Crosshairs type);
	
	void PopToolboxWindow();
	void RefreshToolBoxWindow();

	void PopInfoBox(const wchar_t* message);
	void PopObjectPropertyWindow();
	void PopToolbar();

	void CloseToolboxWindow();
	void CloseObjectPropertiesWindow();
	void CloseToolbar();
};

