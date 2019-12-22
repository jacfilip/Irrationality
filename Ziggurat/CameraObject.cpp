#include "CameraObject.h"
#include "WorkManager.h"

CameraObject::CameraObject(scene::ICameraSceneNode* camera, const wchar_t* name, GameScene* scene)
	: Object(camera, name, scene), cameraNode(camera)
{
	camera->bindTargetAndRotation(true);
	this->cameraNode->setPosition(vector3df(0, 0, -50));
	this->cameraNode->setRotation(vector3df(0, 0, 0));
	this->forward = vector3df(0, 0, 1);

	this->phi = 0.f;
	this->theta = 90.f;
	cameraNode->setTarget(node->getAbsolutePosition() + forward);
}

void CameraObject::Update()
{
	if (this->event->IsKeyDown(EKEY_CODE::KEY_F1))
		this->scene->GetGUIEnvironment()->addCheckBox(true, core::recti(500, 500, 2000, 1000));
}

void CameraObject::Translate(const vector3df& v)
{
	Object::Translate(v);
	this->cameraNode->setTarget(cameraNode->getTarget() + forward);
}

const vector3df& CameraObject::Target() const
{
	return cameraNode->getTarget();
}

void CameraObject::Rotate(const vector3df& v)
{
	theta += v.X;
	phi += v.Y;

	forward = vector3df(theta, phi, 0).rotationToDirection(vector3df(0, 1, 0));

	cameraNode->setTarget(cameraNode->getAbsolutePosition() + forward);
}

void CameraObject::SetForwardVector(const vector3df& v)
{
	this->forward = v;
}

const vector3df& CameraObject::GetForwardVector() const
{
	return forward;
}

