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
	POLY,
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
	Object* AddSprite(vector3df pos, video::ITexture* texture, vector3df norm = vector3df(-90.f, 0.f, -90.f), float size = 1.f, const wchar_t* name = nullptr);
	Object* AddPoly(const std::vector<vector3df>& vertices, video::ITexture* texture, scene::E_PRIMITIVE_TYPE primitiveType = scene::EPT_TRIANGLES, const wchar_t* name = nullptr);
};

