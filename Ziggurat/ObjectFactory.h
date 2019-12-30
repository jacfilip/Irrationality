#pragma once
#include <vector>
#include <string>
#include <map>

#include "irrlicht.h"

using namespace irr;
using namespace core;

using namespace std;

extern class Object;
extern class WorkManager;

enum ObjectType
{
	CUBE = 0,
	PLANE,
	MESH3D,
	SPRITE,
};

class ObjectFactory
{
private:
	core::map<ObjectType, int> objectCounter;
	core::map<std::wstring, Object*> objectsDict;

	WorkManager* wm;

public:
	ObjectFactory(WorkManager* wm);

	Object* AddCube(vector3df pos, vector3df rot = vector3df(0, 0, 0), float size = 1.0f, const wchar_t* name = nullptr);
};

