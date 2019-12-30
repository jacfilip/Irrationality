#pragma once
#include <irrlicht.h>
#include <string>
#include "ObjectFactory.h"

class WorkManager;
class GameScene;
class EventReceiver;

using namespace irr;

using core::vector3df;
using scene::ISceneNode;

using std::wstring;

class Object
{
protected:
	scene::ISceneNode* node;
	wstring name;
	GameScene* scene;
	EventReceiver* event;

public:
	Object(ISceneNode* node, const wchar_t* name, GameScene* scene);

	vector3df Position() { return node->getPosition(); }
	vector3df Rotation() { return node->getRotation(); }

	virtual void Translate(const vector3df& v);
	virtual void Rotate(const vector3df& v);

	virtual void Update() = 0;
};

