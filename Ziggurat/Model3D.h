#pragma once
#include "Object.h"

using core::vector3df;


class Model3D :
	public Object
{
protected:
	ObjectType type;
	video::ITexture* defaultTexture;

	void LevelizeY();

public:
	Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, vector3df scale, 
		ObjectType type, wchar_t* meshPath = nullptr, HitType hitType = HitType(ID_PICKABLE | ID_HIGHLIGHTABLE));

	void Update(u32 deltaT) override;

	virtual void ApplyTexture(const wchar_t* path, int layer = 0) override;
	virtual gui::IGUIWindow* GetPropertiesWindow() override;
	virtual video::ITexture* GetDefaultTexture() override;
};

