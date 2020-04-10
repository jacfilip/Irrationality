#pragma once
#include "Object.h"

class CameraObject :
	public Object
{
private:
	vector3df forward;
	float phi, theta;

public:
	scene::ICameraSceneNode* cameraNode;

	CameraObject(irr::scene::ICameraSceneNode* camera, const wchar_t* name, GameScene* scene);

	virtual void Translate(const vector3df& v) override;
	virtual void Rotate(const vector3df& v) override;

	const vector3df& Target() const;

	void SetForwardVector(const vector3df& v);
	const vector3df& GetForwardVector() const;

	void Update(u32 deltaT) override;
};

