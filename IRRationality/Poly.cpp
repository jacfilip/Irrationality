#include "Poly.h"
#include "GameScene.h"
#include "WorkManager.h"
#include "GUImanager.h"

Poly::Poly(scene::ISceneNode* node, const wchar_t* name, video::ITexture* texture, ObjectType type, GameScene* scene, HitType hitType, const vector<video::S3DVertex>& vertices)
	: Object(node, name, scene, hitType)
{
	this->Vertices =  vertices;
	this->polyNode = node;
}

