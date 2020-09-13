#pragma once
#include <irrlicht.h>
#include <iostream>
#include <string>
#include <vector>

#include "Object.h"
#include "CameraObject.h"
#include "Model3D.h"
#include "EventReceiver.h"
#include "ObjectFactory.h"

using namespace irr;
using irr::core::vector3df;

using std::string;
using std::wstring;

extern class WorkManager;
extern class GUImanager;
extern class EventReceiver;
extern struct EventReceiver::GUIEvent;

class GameScene
{
private:
	WorkManager* wm;
	CameraObject* activeCam;

	gui::IGUIStaticText* camPosCaption;
	gui::IGUIFont* diagnosticFont;

	gui::IGUIEnvironment* guiEnv;

	gui::IGUIFileOpenDialog* textureSelectFileDialog;

	scene::ISceneCollisionManager* colman;

	u32 lastSceneUpdate;
	u32 deltaTime;

public:
	GUImanager* GUI;

	std::vector<Object*> objects;
	ObjectFactory* objFactory;

	Object* selectedObject;

	int gridSnap;

	GameScene(WorkManager* wm);

	void UpdateScene(u32 time);
	void HandleGUIEvents(EventReceiver::GUIEvent& guiEvent);
	gui::IGUIEnvironment* GetGUIEnvironment() const;

	void DrawScene();
	void DrawFloor();
	void ShowDiagnostics(const wchar_t* text);
	
	void AddCamera(const vector3df& pos, const vector3df& lookat);

	EventReceiver* GetEventReceiver();
	WorkManager* GetWorkManager();

	void MoveCamera();

	scene::ISceneCollisionManager* GetCollisionManager() const;
	Object* GetObjectByNode(scene::ISceneNode* node) const;

	void SelectObject(Object* obj);
	void SelectObject(scene::ISceneNode* node);
	void DeselectObject();

	Object* GetSelectedObject();
	Object* FindObject(wstring name);
	void DestroyObject(Object* obj);
};

