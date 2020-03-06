#pragma once

#ifndef GENERATE
#define GENERATE
#include "OpenGLGraphicsObject.h"
#include "GraphicsStructures.h"
#include "OpenGLIndexedGraphicsObject.h"

class Generate
{
public:
   static OpenGLGraphicsObject* FlatSurface(float width, float depth, RGBA color);
   static OpenGLGraphicsObject* Cuboid(float width, float depth, float height, RGBA color);

   static OpenGLIndexedGraphicsObject* IndexedFlatSurface(float width, float depth, RGBA color);
};

#endif

