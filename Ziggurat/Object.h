#pragma once
#include <irrlicht.h>
#include <string>
#include "ObjectFactory.h"
#include "GUImanager.h"

class WorkManager;
class GameScene;
class EventReceiver;

using namespace irr;

using core::vector3df;
using scene::ISceneNode;

using std::wstring;

extern core::vector2di WindowResolution;

enum HitType
{
	ID_NOT_PICKABLE = 0,
	ID_PICKABLE = 1,
	ID_HIGHLIGHTABLE = 1 << 1,
};

class Object
{
protected:
	wstring name;
	GameScene* scene;
	EventReceiver* event;

	HitType hitType;
	scene::ITriangleSelector* selector;
	gui::IGUIWindow* wndProperties;

public:
	scene::ISceneNode* node;

	bool isSelected;

	Object(ISceneNode* node, const wchar_t* name, GameScene* scene, HitType hit = ID_PICKABLE);

	vector3df GetPosition() { return node->getPosition(); }
	vector3df GetRotation() { return node->getRotation(); }

	void SetPosition(const vector3df& pos) { node->setPosition(pos); }
	void SetRotation(const vector3df& rot) { node->setRotation(rot); }

	virtual void Translate(const vector3df& v);
	virtual void Rotate(const vector3df& v);

	virtual void ApplyTexture(const wchar_t* path, int layer);
	virtual video::ITexture* GetDefaultTexture();

	virtual void Update(u32 deltaT);

	const wstring& GetName() { return name; }

	virtual gui::IGUIWindow* GetPropertiesWindow();
};

