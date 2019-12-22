#include "Object.h"
#include "GameScene.h"

Object::Object(ISceneNode* node, const wchar_t* name, GameScene* scene)
{
	this->node = node;
	this->name = name;
	this->scene = scene;
	this->event = scene->GetEventReceiver();
}

void Object::Translate(const vector3df& v)
{
	node->setPosition(node->getPosition() + v);
}
  
void Object::Rotate(const vector3df& v)
{
	node->setRotation(node->getRotation() + v);
}
 