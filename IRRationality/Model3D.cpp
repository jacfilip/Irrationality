#include "Model3D.h"
#include "GameScene.h"
#include "WorkManager.h"
#include "GUImanager.h"

void Model3D::Update(u32 deltaT)
{
	Object::Update(deltaT);
	
	if (this->isSelected)
		if (scene->GetEventReceiver()->IsKeyPressed(KeyMap.SELECTED_Y_ZERO))
			LevelizeY();
}

void Model3D::LevelizeY()
{	
	vector3df edges[8];
	((scene::IMeshSceneNode*)node)->getMesh()->getBoundingBox().getEdges(edges);

	float bottom = edges[0].Y;
	for (int i = 1; i < 8; i++)
	{
		if (edges[i].Y < bottom)
			bottom = edges[i].Y;
	}

	this->Translate(vector3df(0, -this->GetPosition().Y - bottom, 0));
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

video::ITexture* Model3D::GetDefaultTexture()
{
	return defaultTexture;
}

gui::IGUIWindow* Model3D::CreatePropertiesWindow()
{
	Object::CreatePropertiesWindow();

	wndProperties->setText(L"Properties - Model 3D");

	static_cast<gui::IGUIStaticText*>(wndProperties->getElementFromId(1))->setText((this->name).c_str());

	static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_POS_X))->setValue(this->GetPosition().X);
	static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_POS_Y))->setValue(this->GetPosition().Y);
	static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_POS_Z))->setValue(this->GetPosition().Z);

	static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_ROT_X))->setValue(this->GetRotation().X);
	static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_ROT_Y))->setValue(this->GetRotation().Y);
	static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_ROT_Z))->setValue(this->GetRotation().Z);



	return wndProperties;
}

void Model3D::Destroy()
{
	Object::Destroy();
}
