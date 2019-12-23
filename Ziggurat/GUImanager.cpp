#include "GUImanager.h"
#include "GameScene.h"
#include "WorkManager.h"

GUImanager::GUImanager(GameScene* gs)
{
	this->crosshairType = Crosshairs::NONE;
	this->scene = gs;
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

void GUImanager::PopInsertWindow()
{
	this->insertWindow = scene->GetGUIEnvironment()->addWindow(core::recti(10, 10, 110, 260), false, L"Insert", nullptr, GUIElements::INSERT_WND);
}

void GUImanager::CloseInsertWindow()
{
	if (insertWindow != nullptr)
	{
		this->insertWindow->remove();
		this->insertWindow = nullptr;
	}
}
