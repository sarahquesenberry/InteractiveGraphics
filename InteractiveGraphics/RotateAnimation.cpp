#include "RotateAnimation.h"
#include "AbstractGraphicsObject.h"

void RotateAnimation::Update(double elapsedSeconds)
{
	double deltaDegrees = elapsedSeconds * this->_degreesPerSecond;

	this->graphicsObject->frame.Rotate(deltaDegrees, this->_axis);
}
