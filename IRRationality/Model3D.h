#pragma once
#include "Object.h"

using core::vector3df;


class Model3D :
	public Object
{
protected:
	ObjectType type;

	void LevelizeY();

public:
	Model3D(ISceneNode* node, const wchar_t* name, GameScene* scene, vector3df pos, vector3df rot, vector3df scale, 
		ObjectType type, wchar_t* meshPath = nullptr, HitType hitType = HitType(ID_PICKABLE | ID_HIGHLIGHTABLE));

	void Update(u32 deltaT) override;

	virtual gui::IGUIWindow* CreatePropertiesWindow() override;
	virtual video::ITexture* GetDefaultTexture() override;
	virtual void Destroy() override;
};

