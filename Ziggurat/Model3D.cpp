#include "Model3D.h"

void Model3D::Update()
{
	
}

Model3D::Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, vector3df scale, ObjectType type, wchar_t* meshPath)
	: Object(node, name, scene)
{
	this->node->setPosition(pos);
	this->node->setRotation(rot);
	this->node->setScale(scale);

	this->type = type;
}
