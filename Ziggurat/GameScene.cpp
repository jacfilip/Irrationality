#include "GameScene.h"
#include "CameraObject.h"
#include "Model3D.h"

#include "WorkManager.h"
#include "GUImanager.h"

extern class CameraObject;
extern class Model3D;
extern enum ObjectType;

GameScene::GameScene(WorkManager* wm)
	: wm(wm)
{	
	AddCamera(core::vector3df(), core::vector3df(0, 10, 0));
	diagnosticFont = wm->smgr->getGUIEnvironment()->getFont("fonts//fixedsys10.bmp");
	if (!diagnosticFont)
		throw new exception("Font not found.");
	this->guiEnv = wm->smgr->getGUIEnvironment();
	this->guiEnv->getSkin()->setFont(diagnosticFont);
	this->wm->device->getCursorControl()->setActiveIcon(gui::ECURSOR_ICON::ECI_CROSS);
	this->GUI = new GUImanager(this);
	this->objFactory = new ObjectFactory(wm);
	this->selectedObject = nullptr;
	this->colman = wm->smgr->getSceneCollisionManager();
	this->gridSnap = 0;
	this->lastSceneUpdate = 0;
	this->deltaTime = 0;

	camPosCaption = wm->smgr->getGUIEnvironment()->addStaticText(L"", core::recti(0, 0, 1000, 800));
	
	std::cout << "Scene initialized." << std::endl;
}

void GameScene::UpdateScene(u32 time)
{
	deltaTime = time - lastSceneUpdate;

	for (Object* obj : objects)
		obj->Update(deltaTime);

	lastSceneUpdate = time;

}

void GameScene::HandleGUIEvents(EventReceiver::GUIEvent& guiEvent)
{
	s32 id = guiEvent.id;
	
	switch (id)
	{
	case GUIElements::INSERT_WND:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_ELEMENT_CLOSED)
			GUI->CloseToolboxWindow();
		break;
	case GUIElements::OBJ_PROPERTY_BOX_POS_X:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_SPINBOX_CHANGED)
		{
			selectedObject->SetPosition(core::vector3df(static_cast<IGUISpinBox*>(guiEvent.caller)->getValue(),
				selectedObject->GetPosition().Y,
				selectedObject->GetPosition().Z));
		}
		break;
	case GUIElements::OBJ_PROPERTY_BOX_POS_Y:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_SPINBOX_CHANGED)
		{
			selectedObject->SetPosition(core::vector3df(selectedObject->GetPosition().X,
				static_cast<IGUISpinBox*>(guiEvent.caller)->getValue(),
				selectedObject->GetPosition().Z));
		}
		break;
	case GUIElements::OBJ_PROPERTY_BOX_POS_Z:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_SPINBOX_CHANGED)
		{
			selectedObject->SetPosition(core::vector3df(selectedObject->GetPosition().X,
				selectedObject->GetPosition().Y,
				static_cast<IGUISpinBox*>(guiEvent.caller)->getValue()));
		}
		break;
	case GUIElements::OBJ_PROPERTY_BOX_ROT_X:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_SPINBOX_CHANGED)
		{
			selectedObject->SetRotation(core::vector3df(static_cast<IGUISpinBox*>(guiEvent.caller)->getValue(),
				selectedObject->GetRotation().Y,
				selectedObject->GetRotation().Z));
		}
		break;
	case GUIElements::OBJ_PROPERTY_BOX_ROT_Y:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_SPINBOX_CHANGED)
		{
			selectedObject->SetRotation(core::vector3df(selectedObject->GetRotation().X,
				static_cast<IGUISpinBox*>(guiEvent.caller)->getValue(),
				selectedObject->GetRotation().Z));
		}
		break;
	case GUIElements::OBJ_PROPERTY_BOX_ROT_Z:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_SPINBOX_CHANGED)
		{
			selectedObject->SetRotation(core::vector3df(selectedObject->GetRotation().X,
				selectedObject->GetRotation().Y,
				static_cast<IGUISpinBox*>(guiEvent.caller)->getValue()));
		}
		break;
	case GUIElements::TOOL_BOX_OBJ_LIST:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_LISTBOX_CHANGED)
		{
			GUI->CloseObjectPropertiesWindow();
			gui::IGUIListBox* list = dynamic_cast<gui::IGUIListBox*>(guiEvent.caller);
			wstring name = list->getListItem(list->getSelected());
			Object* sel = FindObject(name);
			
			if (sel)
			{
				SelectObject(sel);
				GUI->PopObjectPropertyWindow();
			}
		}
		break;
	case GUIElements::OBJ_PROPERTY_BOX_REMOVE:
		if (guiEvent.type == gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)
			wm->device->getGUIEnvironment()->addMessageBox(L"Removing object.", L"Are you sure you want to remove this object?", true, EMBF_YES | EMBF_NO, 0, OBJ_PROPERTY_BOX_REMOVE_CONFIRM);
		break;
	case GUIElements::OBJ_PROPERTY_BOX_REMOVE_CONFIRM:
		if (guiEvent.type == EGET_MESSAGEBOX_YES && selectedObject)
		{
			selectedObject->Destroy();
			GUI->RefreshToolBoxWindow();
		}
	default:
		break;
	}
}

gui::IGUIEnvironment* GameScene::GetGUIEnvironment() const
{
	return this->guiEnv;
}

void GameScene::DrawScene()
{
	wm->driver->beginScene(true, true, video::SColor(255, 50, 50, 50));
	
	wm->smgr->setAmbientLight(video::SColor(0, 200, 200, 200));
	
	DrawFloor();

	wm->smgr->drawAll();

	wm->device->getGUIEnvironment()->drawAll();

	wm->driver->endScene();
}

void GameScene::DrawFloor()
{
	wm->driver->setTransform(video::E_TRANSFORMATION_STATE::ETS_WORLD, core::IdentityMatrix);

	const vector3df& origin = activeCam->GetPosition();
	
	float dist = 10.f;
	int x0 = (int)(origin.X / dist) * dist;
	int z0 = (int)(origin.Z / dist) * dist;
	int num = 50;
	video::SColor col = video::SColor(255, 180, 180, 180);
	video::SMaterial mat;
	mat.MaterialType = video::E_MATERIAL_TYPE::EMT_SOLID;
	mat.AmbientColor = col;
	wm->driver->setMaterial(mat);
	
	for (int i = -num; i <= num; ++i)
	{
		wm->driver->draw3DLine(vector3df(i * dist + x0, 0, -num * dist + z0), vector3df(i * dist + x0, 0, num * dist + z0), col);
		wm->driver->draw3DLine(vector3df(-num * dist + x0, 0, i * dist + z0), vector3df(num * dist + x0, 0, i * dist + z0), col);
	}
}

void GameScene::ShowDiagnostics(const wchar_t* text)
{
	camPosCaption->setText(text);
}

void GameScene::AddCamera(const vector3df& pos, const vector3df& lookat)
{
	activeCam = new CameraObject(wm->smgr->addCameraSceneNode(nullptr, pos, lookat), L"Main Camera", this);
}

EventReceiver* GameScene::GetEventReceiver()
{
	return wm->eventReceiver;
}

WorkManager* GameScene::GetWorkManager()
{
	return this->wm;
}

void GameScene::MoveCamera()
{
	const float camSpeed = 0.1f;
	const float camRotSpeed = 0.03f;

	if (wm->eventReceiver->IsKeyDown(KeyMap.CAMERA_FORWARD))
		activeCam->Translate(activeCam->cameraNode->getRotation().rotationToDirection().normalize() * camSpeed);
	else if (wm->eventReceiver->IsKeyDown(KeyMap.CAMERA_BACK))
		activeCam->Translate(-activeCam->cameraNode->getRotation().rotationToDirection().normalize() * camSpeed);

	if (wm->eventReceiver->IsKeyDown(KeyMap.CAMERA_LEFT))
		activeCam->Translate(activeCam->cameraNode->getRotation().rotationToDirection().crossProduct(activeCam->cameraNode->getUpVector()).normalize() * camSpeed);
	else if (wm->eventReceiver->IsKeyDown(KeyMap.CAMERA_RIGHT))
		activeCam->Translate(-activeCam->cameraNode->getRotation().rotationToDirection().crossProduct(activeCam->cameraNode->getUpVector()).normalize() * camSpeed);

	if (wm->eventReceiver->IsKeyDown(KeyMap.CAMERA_UP))
		activeCam->Translate(vector3df(0, 1, 0) * camSpeed);
	else if (wm->eventReceiver->IsKeyDown(KeyMap.CAMERA_DOWN))
		activeCam->Translate(vector3df(0, -1, 0) * camSpeed);
	
	if (wm->eventReceiver->mouseState.shift().getLength() > 0)
	{
		activeCam->Rotate(vector3df(wm->eventReceiver->mouseState.shift().Y * camRotSpeed,
									wm->eventReceiver->mouseState.shift().X * camRotSpeed,
									0
									));
	}

	wstring camPos = L"Pos: {X: " + std::to_wstring(activeCam->GetPosition().X) + L", "
		+ L"Y: " + std::to_wstring(activeCam->GetPosition().Y) + L" "
		+ L"Z: " + std::to_wstring(activeCam->GetPosition().Z) + L"}\n";

	wstring camRot = L"Rot: {X: " + std::to_wstring(activeCam->GetRotation().X) + L", "
		+ L"Y: " + std::to_wstring(activeCam->GetRotation().Y) + L" "
		+ L"Z: " + std::to_wstring(activeCam->GetRotation().Z) + L"}\n";

	ShowDiagnostics((camPos + camRot).c_str());
}

scene::ISceneCollisionManager* GameScene::GetCollisionManager() const
{
	return colman;
}

Object* GameScene::GetObjectByNode(scene::ISceneNode* node) const
{
	for (Object* obj : objects)
		if (obj->node == node)
			return obj;
	return nullptr;
}

void GameScene::SelectObject(Object* obj)
{
	if (!obj)
		return;

	if (selectedObject)
		DeselectObject();

	selectedObject = obj;
	selectedObject->isSelected = true;

	obj->node->getMaterial(0).AmbientColor = video::SColor(100, 220, 50, 220);
}

void GameScene::SelectObject(scene::ISceneNode* node)
{
	SelectObject(GetObjectByNode(node));
}

void GameScene::DeselectObject()
{
	if (selectedObject)
	{
		selectedObject->node->getMaterial(0).AmbientColor = video::SColor(255, 255, 255, 255);
		selectedObject->isSelected = false;
	}

	selectedObject = nullptr;
}

Object* GameScene::GetSelectedObject()
{
	return selectedObject;
}

Object* GameScene::FindObject(wstring name)
{
	for (Object* obj : objects)
		if (obj->GetName() == name)
			return obj;

	return nullptr;
}

void GameScene::DestroyObject(Object* obj)
{
	for (auto i = objects.begin(); i != objects.end(); i++)
	{
		if (*i == obj)
		{
			objects.erase(i);
			return;
		}
	}
}


