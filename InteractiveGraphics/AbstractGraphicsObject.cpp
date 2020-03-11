#include "AbstractGraphicsObject.h"
#include "AbstractAnimation.h"

AbstractGraphicsObject::~AbstractGraphicsObject()
{
   if (this->vertexStrategy != nullptr) {
      delete this->vertexStrategy;
   }

   if (this->animation != nullptr) {
       delete this->animation;
   }
}

void AbstractGraphicsObject::Update(double elapsedSeconds)
{
    if (this->animation != nullptr) {
        this->animation->Update(elapsedSeconds);
    }
}
