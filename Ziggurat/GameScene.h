#pragma once
#include <irrlicht.h>
#include <iostream>
#include <string>
#include <vector>

#include "Object.h"
#include "CameraObject.h"
#include "Model3D.h"
#include "EventReceiver.h"

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

	std::vector<Object*> objects;

	gui::IGUIStaticText* camPosCaption;
	gui::IGUIFont* diagnosticFont;

	gui::IGUIEnvironment* guiEnv;

public:
	GUImanager* GUI;

	GameScene(WorkManager* wm);

	void UpdateScene();
	void HandleGUIEvents(EventReceiver::GUIEvent& guiEvent);
	gui::IGUIEnvironment* GetGUIEnvironment() const;

	void DrawScene();
	void ShowDiagnostics(const wchar_t* text);
	
	void AddCamera(const vector3df& pos, const vector3df& lookat);
	Model3D* AddCube(vector3df pos, vector3df rot = vector3df(0, 0, 0), float size = 1.0f);

	EventReceiver* GetEventReceiver();
	WorkManager* GetWorkManager();

	void MoveCamera();
};

