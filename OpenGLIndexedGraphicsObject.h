#pragma once
#ifndef OPENGL_INDEXED_GRAPHCS_OBJECT 
#define OPENGL_INDEXED_GRAPHCS_OBJECT



#include "OpenGLGraphicsObject.h"
class OpenGLIndexedGraphicsObject :
	public OpenGLGraphicsObject
{
protected:
	GLuint _indexVbo;
	vector<unsigned int> _indexes;

public:
	OpenGLIndexedGraphicsObject();
	OpenGLIndexedGraphicsObject(AbstractGraphicsShader* shader);
};

#endif