#include "Sprite.h"

Sprite::Sprite(ISceneNode* node, const wchar_t* name, vector3df pos, vector3df norm, float scale,
	video::ITexture* texture, ObjectType type, GameScene* scene, HitType hitType) 
	: Object(node, name, scene, hitType)
{

}

void Sprite::Update(u32 deltaT)
{

}
