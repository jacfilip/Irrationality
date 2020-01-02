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
		break;
	default:
			break;
	}
}

void GUImanager::PopToolboxWindow()
{
	this->toolboxWindow = scene->GetGUIEnvironment()->addWindow(core::recti(10, 20, 175, 0.9 * WindowResolution.Y), false, L"Toolbox", nullptr, GUIElements::INSERT_WND);
}

void GUImanager::PopInfoBox(const wchar_t* message)
{
	scene->GetGUIEnvironment()->addMessageBox(L"Warning!", message, true);
}

void GUImanager::CloseToolboxWindow()
{
	if (toolboxWindow != nullptr)
	{
		this->toolboxWindow->remove();
		this->toolboxWindow = nullptr;
	}
}
