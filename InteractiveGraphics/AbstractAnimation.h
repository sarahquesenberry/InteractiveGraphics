#pragma once
#include "ReferenceFrame.h"
class AbstractGraphicsObject;

class AbstractAnimation
{
public:
	
	AbstractGraphicsObject* graphicsObject;

	AbstractAnimation() { graphicsObject = nullptr; }

	virtual void Update(double elapsedSeconds) = 0;

	
};

