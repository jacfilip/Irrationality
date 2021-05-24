#include "Sprite.h"
#include "GameScene.h"

Sprite::Sprite(ISceneNode* node, const wchar_t* name, vector3df pos, vector3df norm, float scale,
	video::ITexture* texture, ObjectType type, GameScene* scene, HitType hitType) 
	: Object(node, name, scene, hitType)
{
	this->IsLockedZ = true;
}

void Sprite::Update(u32 deltaT)
{
	core::vector3df cam = this->scene->GetCameraPosition();
	core::vector3df lookat = this->scene->GetCameraLookaAt();

	this->node->setRotation( -(cam - this->GetPosition()).normalize() * 180 / 3.141592 );
}
