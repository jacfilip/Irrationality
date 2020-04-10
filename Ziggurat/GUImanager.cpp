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
	}
	else
	{
		this->toolboxWindow->setVisible(true);
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

	propertiesWindow = obj->GetPropertiesWindow();

	if (propertiesWindow != nullptr)
		propertiesWindow->setVisible(true);
}

void GUImanager::CloseToolboxWindow()
{
	if (toolboxWindow != nullptr)
	{
		this->toolboxWindow->setVisible(false);
	}
}

void GUImanager::CloseObjectPropertiesWindow()
{
	if (propertiesWindow != nullptr)
	{
		propertiesWindow->setVisible(false);
	}
}
