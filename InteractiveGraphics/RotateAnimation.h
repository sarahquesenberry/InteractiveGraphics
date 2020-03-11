#pragma once
#include "AbstractAnimation.h"
class RotateAnimation :
	public AbstractAnimation
{
protected:
	double _degreesPerSecond;
	glm::vec3 _axis;

public:
	RotateAnimation(double degreesPerSecond = 90, glm::vec3 axis = glm::vec3(0, 1, 0)) { 
		_degreesPerSecond = degreesPerSecond; 
		_axis = axis; };

	void Update(double elapsedSeconds);
};

