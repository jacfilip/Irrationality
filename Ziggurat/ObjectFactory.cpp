#include "ObjectFactory.h"
#include "WorkManager.h"
#include "GUImanager.h"
#include "Sprite.h"

using namespace irr::core;


ObjectFactory::ObjectFactory(WorkManager* wm)
	: wm(wm)
{
	objectCounter.insert(ObjectType::CUBE, 0);
	objectCounter.insert(ObjectType::MESH3D, 0);
	objectCounter.insert(ObjectType::PLANE, 0);
	objectCounter.insert(ObjectType::SPRITE, 0);
}

Object* ObjectFactory::AddCube(vector3df pos, vector3df rot, float size, const wchar_t* name)
{
	std::wstring namestr;
	if (name == nullptr)
	{
		std::wstring defaultName = std::wstring(L"Cube_") + std::wstring(std::to_wstring(objectCounter[ObjectType::CUBE] + 1));
		namestr = defaultName;
	}
	else
	{
		namestr = name;
	}


	if (objectsDict.find(namestr))
	{
		std::wstring buf = std::wstring(L"Object '") + std::wstring(name) + std::wstring(L"' already exists. Choose another name.");
		wm->GetActiveScene()->GUI->PopInfoBox(buf.c_str());
		return nullptr;
	}
	scene::ISceneNode* cube = wm->smgr->addCubeSceneNode(10, nullptr, 0, pos);
	cube->getMaterial(0).DiffuseColor.set(255, 255, 255, 255);
	cube->getMaterial(0).MaterialType = video::EMT_SOLID_2_LAYER;
	cube->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, true);
	cube->setMaterialType(video::E_MATERIAL_TYPE::EMT_SOLID);
	cube->getMaterial(0).BackfaceCulling = false;
	
	objectCounter[ObjectType::CUBE] = objectCounter[ObjectType::CUBE] + 1;

	objectsDict.insert(namestr, new Model3D(cube, namestr.c_str(), wm->GetActiveScene(), pos, rot, core::vector3df(1, 1, 1) * size, ObjectType::CUBE));

	return objectsDict[namestr];
}

Object* ObjectFactory::AddSprite(vector3df pos, video::ITexture* texture, vector3df norm, float size, const wchar_t* name)
{
	std::wstring namestr;
	if (name == nullptr)
	{
		std::wstring defaultName = std::wstring(L"Sprite_") + std::wstring(std::to_wstring(objectCounter[ObjectType::SPRITE] + 1));
		namestr = defaultName;
	}
	else
	{
		namestr = name;
	}

	if (objectsDict.find(namestr))
	{
		wm->GetActiveScene()->GUI->PopInfoBox((std::wstring(L"Object '") + std::wstring(name) + std::wstring(L"' already exists. Choose another name.")).c_str());
		return nullptr;
	}

	scene::ISceneNode* sprite= wm->smgr->addMeshSceneNode(
		wm->smgr->getGeometryCreator()->createPlaneMesh(core::dimension2df(10, 10), 
			core::dimension2du(1,1), 0, core::dimension2df(1,1)),
		nullptr, 0, pos, norm, vector3df(size, size, size)
	);
	sprite->getMaterial(0).setTexture(0, texture);

	objectCounter[ObjectType::SPRITE] = objectCounter[ObjectType::SPRITE] + 1;
	objectsDict.insert(namestr, new Sprite(sprite, namestr.c_str(), pos, norm, size, texture, ObjectType::SPRITE, wm->GetActiveScene()));

	return objectsDict[namestr];
}
