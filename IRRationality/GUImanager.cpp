#include "GUImanager.h"
#include "GameScene.h"
#include "WorkManager.h"

extern core::vector2di WindowResolution;

GUImanager::GUImanager(GameScene* gs)
{
	this->crosshairType = Crosshairs::NONE;
	this->scene = gs;
	
	IGUISkin* skin = scene->GetGUIEnvironment()->getSkin();
	
	for (s32 i = 0; i < irr::gui::EGDC_COUNT; ++i)
	{
		video::SColor col  = skin->getColor((gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		skin->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
}

void GUImanager::SetCrosshair(Crosshairs type)
{
	this->crosshairType = type;
	switch (type)
	{
	case NONE:
		scene->GetWorkManager()->device->getCursorControl()->setActiveIcon(ECI_NO);
		break;
	case CROSS:
		scene->GetWorkManager()->device->getCursorControl()->setActiveIcon(ECI_CROSS);
		break;
	case POINTER:
		scene->GetWorkManager()->device->getCursorControl()->setActiveIcon(ECI_NORMAL);
		break;
	default:
			break;
	}
}

void GUImanager::PopToolboxWindow()
{
	if (this->toolboxWindow == nullptr)
	{
		this->toolboxWindow = scene->GetGUIEnvironment()->addWindow(core::recti(10, 20, 175, 0.9 * WindowResolution.Y), false, L"Toolbox", nullptr, GUIElements::INSERT_WND);
		scene->GetGUIEnvironment()->addStaticText(L"Add object:", core::recti(5, 25, 150, 40), false, false, toolboxWindow);
		this->objAddComboBox = scene->GetGUIEnvironment()->addComboBox(core::recti(10, 45, 150, 65), toolboxWindow, GUIElements::OBJ_ADD_COMBO_BOX);
		this->objAddComboBox->addItem(L"Cube");
		this->objAddComboBox->addItem(L"Plane");
		this->toolboxWindow->getCloseButton()->setVisible(false);

		scene->GetGUIEnvironment()->addStaticText(L"Objects:", core::recti(10, 70, 150, 85), false, false, toolboxWindow);
		this->objectList = scene->GetGUIEnvironment()->addListBox(core::recti(10, 90, 150, 350), toolboxWindow, GUIElements::TOOL_BOX_OBJ_LIST, true);

		this->objectList->clear();
		for (auto obj : scene->objects)
			this->objectList->addItem(obj->GetName().c_str());
	}
	else
	{
		this->toolboxWindow->setVisible(true);
		for (auto e : toolboxWindow->getChildren())
			e->setEnabled(true);
	}
}

void GUImanager::RefreshToolBoxWindow()
{
	if (toolboxWindow)
	{
		this->objectList->clear();
		for (auto obj : scene->objects)
			this->objectList->addItem(obj->GetName().c_str());
	}
}

void GUImanager::PopInfoBox(const wchar_t* message)
{
	scene->GetGUIEnvironment()->addMessageBox(L"Warning!", message, true);
}

void GUImanager::PopObjectPropertyWindow()
{
	Object* obj = scene->GetSelectedObject();
	if (obj == nullptr)
		return;

	CloseObjectPropertiesWindow();

	propertiesWindow = obj->CreatePropertiesWindow();

	if (propertiesWindow)
	{
		propertiesWindow->setVisible(true);
		for (auto e : propertiesWindow->getChildren())
			e->setEnabled(true);
	}
}

void GUImanager::CloseToolboxWindow()
{
	if (toolboxWindow)
	{
		this->toolboxWindow->setVisible(false);
		for (auto e : toolboxWindow->getChildren())
			e->setEnabled(false);
	}
}

void GUImanager::CloseObjectPropertiesWindow()
{
	if (propertiesWindow)
	{
		this->propertiesWindow->setVisible(false);
		for (auto e : propertiesWindow->getChildren())
			e->setEnabled(false);
	}
}

void GUImanager::PopToolbar()
{
	if (menu == nullptr)
	{
		menu = scene->GetGUIEnvironment()->addMenu(nullptr, MENUSTRIP);
		menu->addItem(L"File", MENUSTRIP_FILE, true, true);
		menu->getSubMenu(0)->addItem(L"Exit", MENUSTRIP_FILE_EXIT);
	}
	else
		menu->setVisible(true);
}

void GUImanager::CloseToolbar()
{
	if (menu)
		menu->setVisible(false);
}

