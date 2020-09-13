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

void Object::Update(u32 deltaT)
{
	if (this->isSelected)
	{
		f32 moveSpeed = 0.1f;
		f32 dist = moveSpeed * deltaT;

		if (scene->GetEventReceiver()->IsKeyDown(KeyMap.SELECTED_X_POS))
		{
			this->Translate(core::vector3df(dist, 0, 0));
		}
		else if (scene->GetEventReceiver()->IsKeyDown(KeyMap.SELECTED_X_NEG))
		{
			this->Translate(core::vector3df(-dist, 0, 0));
		}
		else if (scene->GetEventReceiver()->IsKeyDown(KeyMap.SELECTED_Y_POS))
		{
			this->Translate(core::vector3df(0, dist, 0));
		}
		else if (scene->GetEventReceiver()->IsKeyDown(KeyMap.SELECTED_Y_NEG))
		{
			this->Translate(core::vector3df(0, -dist, 0));
		}
		else if (scene->GetEventReceiver()->IsKeyDown(KeyMap.SELECTED_Z_POS))
		{
			this->Translate(core::vector3df(0, 0, dist));
		}
		else if (scene->GetEventReceiver()->IsKeyDown(KeyMap.SELECTED_Z_NEG))
		{
			this->Translate(core::vector3df(0, 0, -dist));
		}
	}
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

gui::IGUIWindow* Object::CreatePropertiesWindow()
{
	gui::IGUIEnvironment* env = this->scene->GetGUIEnvironment();

	if (wndProperties == nullptr)
	{
		int ystart = 30;
		int vline = 15;
		int voffset = 3, hoffset = 110;

		wndProperties = env->addWindow(core::recti(390, 120, 620, 300), false, L"Properties", 0, GUIElements::OBJ_PROPERTY_BOX);
		wndProperties->getCloseButton()->setVisible(false);

		env->addStaticText(L"NAME:", core::recti(10, ystart, 80, ystart + vline), false, false, wndProperties);
		env->addStaticText(this->name.c_str(), core::recti(85, ystart, 180, ystart + vline), false, false, wndProperties, 1);

		//POSITION SPINBOXES
		env->addStaticText(L"POSITION:", core::recti(10, ystart + (vline + voffset) * 1, 80, ystart + (vline + voffset) * 1 + vline), false, false, wndProperties);
		env->addStaticText(L"X:", core::recti(15, ystart + (vline + voffset) * 2, 80, ystart + (vline + voffset) * 2 + vline), false, false, wndProperties);
		env->addSpinBox(L"0", core::recti(45, ystart + (vline + voffset) * 2, 110, ystart + (vline + voffset) * 2 + vline), true, wndProperties, OBJ_PROPERTY_BOX_POS_X);
		env->addStaticText(L"Y:", core::recti(15, ystart + (vline + voffset) * 3, 80, ystart + (vline + voffset) * 3 + vline), false, false, wndProperties);
		env->addSpinBox(L"0", core::recti(45, ystart + (vline + voffset) * 3, 110, ystart + (vline + voffset) * 3 + vline), true, wndProperties, OBJ_PROPERTY_BOX_POS_Y);
		env->addStaticText(L"Z:", core::recti(15, ystart + (vline + voffset) * 4, 80, ystart + (vline + voffset) * 4 + vline), false, false, wndProperties);
		env->addSpinBox(L"0", core::recti(45, ystart + (vline + voffset) * 4, 110, ystart + (vline + voffset) * 4 + vline), true, wndProperties, OBJ_PROPERTY_BOX_POS_Z);

		static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_POS_X))->setDecimalPlaces(0);
		static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_POS_Y))->setDecimalPlaces(0);
		static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_POS_Z))->setDecimalPlaces(0);

		//ROTATION SPINBOXES
		env->addStaticText(L"ROTATION:", core::recti(10 + hoffset, ystart + (vline + voffset) * 1, 80 + hoffset, ystart + (vline + voffset) * 1 + vline), false, false, wndProperties);
		env->addStaticText(L"X:", core::recti(15 + hoffset, ystart + (vline + voffset) * 2, 80 + hoffset, ystart + (vline + voffset) * 2 + vline), false, false, wndProperties);
		env->addSpinBox(L"0", core::recti(45 + hoffset, ystart + (vline + voffset) * 2, 110 + hoffset, ystart + (vline + voffset) * 2 + vline), true, wndProperties, OBJ_PROPERTY_BOX_ROT_X);
		env->addStaticText(L"Y:", core::recti(15 + hoffset, ystart + (vline + voffset) * 3, 80 + hoffset, ystart + (vline + voffset) * 3 + vline), false, false, wndProperties);
		env->addSpinBox(L"0", core::recti(45 + hoffset, ystart + (vline + voffset) * 3, 110 + hoffset, ystart + (vline + voffset) * 3 + vline), true, wndProperties, OBJ_PROPERTY_BOX_ROT_Y);
		env->addStaticText(L"Z:", core::recti(15 + hoffset, ystart + (vline + voffset) * 4, 80 + hoffset, ystart + (vline + voffset) * 4 + vline), false, false, wndProperties);
		env->addSpinBox(L"0", core::recti(45 + hoffset, ystart + (vline + voffset) * 4, 110 + hoffset, ystart + (vline + voffset) * 4 + vline), true, wndProperties, OBJ_PROPERTY_BOX_ROT_Z);

		static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_ROT_X))->setDecimalPlaces(0);
		static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_ROT_Y))->setDecimalPlaces(0);
		static_cast<gui::IGUISpinBox*>(wndProperties->getElementFromId(OBJ_PROPERTY_BOX_ROT_Z))->setDecimalPlaces(0);

		//TEXTURE SELECT
		env->addButton(core::recti(10, ystart + (vline + voffset) * 5, 35, ystart + (vline + voffset) * 5 + vline), wndProperties, OBJ_PROPERTY_BOX_TEXTURE_SET, L"Set", L"Select texture for this object");
		env->addStaticText(L"Texture:", core::recti(40, ystart + (vline + voffset) * 5, 80 + hoffset, ystart + (vline + voffset) * 5 + vline), false, false, wndProperties, false);

		env->addButton(core::recti(120, ystart + (vline + voffset) * 7, 120 + 100, ystart + (vline + voffset) * 7 + 20), wndProperties, OBJ_PROPERTY_BOX_REMOVE, L"Remove");
	}

	return wndProperties;
}

void Object::Destroy()
{
	scene->DestroyObject(this);
	scene->DeselectObject();
	this->node->remove();
}
