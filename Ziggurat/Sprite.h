#pragma once
#include "Object.h"
class Sprite :
	public Object
{
public:
	void Update(u32 deltaT) override;
};

