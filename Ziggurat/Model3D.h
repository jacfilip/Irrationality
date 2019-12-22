#pragma once
#include "Object.h"

using core::vector3df;

enum ModelType
{
	CUBE,
	PLANE,
	SPHERE,
	MESH
};

class Model3D :
	public Object
{
private:
	ModelType type;

public:
	Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, vector3df scale, ModelType type, wchar_t* meshPath = nullptr);

	void Update() override;
};

