#include "Object.h"
#include "GameScene.h"
#include "WorkManager.h"

Object::Object(ISceneNode* node, const wchar_t* name, GameScene* scene, HitType hit)
{
	this->node = node;
	this->name = name;
	this->scene = scene;
	this->event = scene->GetEventReceiver();
	this->hitType = hit;
	this->selector = nullptr;
	this->isSelected = false;
	this->scene->objects.push_back(this);

	node->setID(this->hitType);
}

void Object::Translate(const vector3df& v)
{
	node->setPosition(node->getPosition() + v);
}
  
void Object::Rotate(const vector3df& v)
{
	node->setRotation(node->getRotation() + v);
}

void Object::ApplyTexture(const wchar_t* path, int layer = 0) {}
 
video::ITexture* Object::GetDefaultTexture()
{
	return nullptr;
}