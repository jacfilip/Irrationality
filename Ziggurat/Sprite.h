#pragma once
#include "Object.h"
class Sprite :
	public Object
{
public:
	Sprite(ISceneNode* node, const wchar_t* name, vector3df pos, vector3df norm, float scale,
		video::ITexture* texture, ObjectType type, GameScene* scene, HitType hitType = HitType(ID_PICKABLE | ID_HIGHLIGHTABLE));
	void Update(u32 deltaT) override;
};

