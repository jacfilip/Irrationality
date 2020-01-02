#include "Model3D.h"
#include "GameScene.h"
#include "WorkManager.h"

void Model3D::Update()
{
	
}

Model3D::Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, 
	vector3df scale, ObjectType type, wchar_t* meshPath, HitType hitType)
	: Object(node, name, scene, hitType)
{
	this->node->setPosition(pos);
	this->node->setRotation(rot);
	this->node->setScale(scale);

	this->type = type;
	this->selector = scene->GetWorkManager()->smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node, 128);
	this->node->setTriangleSelector(selector);
	this->selector->drop();
}

void Model3D::ApplyTexture(const wchar_t* path, int layer)
{
	this->defaultTexture = this->scene->GetWorkManager()->driver->getTexture(path);
	this->node->setMaterialTexture(layer, defaultTexture);
}

video::ITexture* Model3D::GetDefaultTexture()
{
	return defaultTexture;
}
