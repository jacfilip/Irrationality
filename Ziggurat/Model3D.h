#pragma once
#include "Object.h"

using core::vector3df;


class Model3D :
	public Object
{
private:
	ObjectType type;

public:
	Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, vector3df scale, ObjectType type, wchar_t* meshPath = nullptr);

	void Update() override;
};

