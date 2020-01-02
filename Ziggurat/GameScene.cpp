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

	camPosCaption = wm->smgr->getGUIEnvironment()->addStaticText(L"", core::recti(0, 0, 1000, 800));
	
	std::cout << "Scene initialized." << std::endl;
}

void GameScene::UpdateScene()
{
	for(Object* obj : objects)
		obj->Update();
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
	wm->driver->beginScene(true, true, video::SColor(255, 113, 113, 133));
	
	wm->smgr->setAmbientLight(video::SColor(0, 200, 200, 200));
	
	DrawFloor();

	wm->smgr->drawAll();

	wm->device->getGUIEnvironment()->drawAll();

	wm->driver->endScene();
}

void GameScene::DrawFloor()
{
	const vector3df& origin = activeCam->Position();

	float dist = 10.f;
	int x0 = (int)(origin.X / dist) * dist;
	int z0 = (int)(origin.Z / dist) * dist;
	int num = 50;
	video::SColor col = video::SColor(0, 155, 0, 0);
	video::SMaterial mat;
	mat.MaterialType = video::E_MATERIAL_TYPE::EMT_SOLID;
	
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
	objects.push_back(activeCam);
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

	if (wm->eventReceiver->IsKeyDown(KEY_KEY_W))
		activeCam->Translate(activeCam->cameraNode->getRotation().rotationToDirection().normalize() * camSpeed);
	else if (wm->eventReceiver->IsKeyDown(KEY_KEY_S))
		activeCam->Translate(-activeCam->cameraNode->getRotation().rotationToDirection().normalize() * camSpeed);

	if (wm->eventReceiver->IsKeyDown(KEY_KEY_A))
		activeCam->Translate(activeCam->cameraNode->getRotation().rotationToDirection().crossProduct(activeCam->cameraNode->getUpVector()).normalize() * camSpeed);
	else if (wm->eventReceiver->IsKeyDown(KEY_KEY_D))
		activeCam->Translate(-activeCam->cameraNode->getRotation().rotationToDirection().crossProduct(activeCam->cameraNode->getUpVector()).normalize() * camSpeed);

	if (wm->eventReceiver->IsKeyDown(KEY_SPACE))
		activeCam->Translate(vector3df(0, 1, 0) * camSpeed);
	else if (wm->eventReceiver->IsKeyDown(KEY_KEY_C))
		activeCam->Translate(vector3df(0, -1, 0) * camSpeed);
	
	if (wm->eventReceiver->mouseState.shift().getLength() > 0)
	{
		activeCam->Rotate(vector3df(wm->eventReceiver->mouseState.shift().Y * camRotSpeed,
									wm->eventReceiver->mouseState.shift().X * camRotSpeed,
									0
									));
	}

	wstring camPos = L"Pos: {X: " + std::to_wstring(activeCam->Position().X) + L", "
		+ L"Y: " + std::to_wstring(activeCam->Position().Y) + L" "
		+ L"Z: " + std::to_wstring(activeCam->Position().Z) + L"}\n";

	wstring camRot = L"Rot: {X: " + std::to_wstring(activeCam->Rotation().X) + L", "
		+ L"Y: " + std::to_wstring(activeCam->Rotation().Y) + L" "
		+ L"Z: " + std::to_wstring(activeCam->Rotation().Z) + L"}\n";

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


