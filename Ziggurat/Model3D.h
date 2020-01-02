#pragma once
#include "Object.h"

using core::vector3df;


class Model3D :
	public Object
{
private:
	ObjectType type;
	video::ITexture* defaultTexture;

public:
	Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, vector3df scale, 
		ObjectType type, wchar_t* meshPath = nullptr, HitType hitType = HitType(ID_PICKABLE | ID_HIGHLIGHTABLE));

	void Update() override;

	virtual void ApplyTexture(const wchar_t* path, int layer = 0) override;
	virtual video::ITexture* GetDefaultTexture() override;
};

