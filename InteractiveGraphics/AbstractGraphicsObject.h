#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT
#include "AbstractGraphicsShader.h"
#include <glm/glm.hpp>
#include "AbstractTexture.h"
#include "AbstractVertexStrategy.h"
#include "ReferenceFrame.h"

class AbstractAnimation;

class AbstractGraphicsObject
{
    
protected:
   AbstractGraphicsShader* _shader;
   AbstractTexture* _texture;

public:
   AbstractVertexStrategy* vertexStrategy;
   AbstractAnimation* animation;

   ReferenceFrame frame;

public:
   AbstractGraphicsObject() : 
       _shader(nullptr), _texture(nullptr), vertexStrategy(nullptr), animation(nullptr) {}
   AbstractGraphicsObject(
      AbstractGraphicsShader* shader,
      AbstractTexture* texture = nullptr) :
      _shader(shader), vertexStrategy(nullptr), _texture(nullptr), animation(nullptr) {}
   virtual ~AbstractGraphicsObject();
   virtual void SetShader(AbstractGraphicsShader* shader) {
      _shader = shader;
   }
   virtual void SetTexture(AbstractTexture* texture) {
      _texture = texture;
   }
   virtual void Setup() = 0;
   virtual void Render() = 0;

   virtual void Update(double elapsedSeconds);
};

#endif

