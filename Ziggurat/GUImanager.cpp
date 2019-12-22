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
