#pragma once
#ifndef OPENGL_GRAPHICS_SYSTEM
#define OPENGL_GRAPHICS_SYSTEM

#include <glad/glad.h> 
#include "AbstractGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include <GLFW/glfw3.h>



class OpenGLGraphicsSystem :
   public AbstractGraphicsSystem
{
private:
   GLuint _shaderProgram;

private:

   void ProcessInput();
   bool SetupShaders();
   GLuint CompileShader(GLenum type, const GLchar* source);
   GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);

public:
   bool InitializeContext();
   void ShowWindow();
   void Setup();
   void Run();

   OpenGLGraphicsSystem();

   OpenGLGraphicsSystem(OpenGLGraphicsWindow* window);
};

#endif

