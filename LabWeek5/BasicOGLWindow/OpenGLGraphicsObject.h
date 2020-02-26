#pragma once
#include <glad\glad.h>
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"

class OpenGLGraphicsObject :
	public AbstractGraphicsObject
{
private:
	GLuint _vaoId, _vboId;
	GLsizei _arraySize;
	Vertex * _objectData;


public:
	OpenGLGraphicsObject();

	~OpenGLGraphicsObject();

	void SetObjectData(Vertex* objectData, GLsizei size);

	void Setup();
	void Render(unsigned int shaderProgramId);

};

