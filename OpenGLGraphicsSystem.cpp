#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

#include <iostream>
#include <sstream>

OpenGLGraphicsSystem::OpenGLGraphicsSystem() : AbstractGraphicsSystem()
{
   _window = new OpenGLGraphicsWindow("OpenGL Window", 800, 600);
}

OpenGLGraphicsSystem::OpenGLGraphicsSystem(
   OpenGLGraphicsWindow* window, GLSLGraphicsShader* shader):
   AbstractGraphicsSystem(window, shader)
{
}

OpenGLGraphicsSystem::~OpenGLGraphicsSystem()
{
   glfwTerminate();
}

bool OpenGLGraphicsSystem::InitializeContext()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   if (!_window->Create()) {
      glfwTerminate();
      return false;
   }
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      _errorReport = "Failed to initialize GLAD\n";
      return false;
   }
   if (_shader != nullptr) {
      if (!_shader->Create()) {
         _errorReport = _shader->ReportErrors();
         return false;
      }
   }
   else {
      _errorReport = "A shader was not created.\n";
      return false;
   }
   return true;
}

void OpenGLGraphicsSystem::ShowWindow()
{
   _window->SetOnResize();
   _window->ShowMaximized();
}

void OpenGLGraphicsSystem::Setup()
{
   _object->Setup();
}

void OpenGLGraphicsSystem::Run()
{
   while (!_window->IsTimeToClose()) {
      ProcessInput();

<<<<<<< Updated upstream
=======
      _camera->SetupProjectionAndView(_window->GetAspectRatio());
      _camera->SetupLookingForward();
      shader->projection = _camera->GetProjection();
      shader->view = _camera->GetView();
 
>>>>>>> Stashed changes
      _window->Clear();
      _object->Render();

      _window->SwapBuffers();
   }
}

void OpenGLGraphicsSystem::ProcessInput()
{
   if (_window->GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      _window->Close();
   }
<<<<<<< Updated upstream
=======
   auto cube = (OpenGLGraphicsObject*)_objects["Cube"];
   if (_window->GetKeyState(GLFW_KEY_Y) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(0, 1, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_X) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(1, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_Z) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(0, 0, 1));
   }
   if (_window->GetKeyState(GLFW_KEY_R) == GLFW_PRESS) {
      cube->frame.Reset();
   }


   auto cuboid1 = (OpenGLGraphicsObject*)_objects["Cuboid1"];
   if (_window->GetKeyState(GLFW_KEY_I) == GLFW_PRESS) {
       cuboid1->frame.RotateWorld(1, glm::vec3(0, 1, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_J) == GLFW_PRESS) {
       cuboid1->frame.Rotate(1, glm::vec3(1, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_K) == GLFW_PRESS) {
       cuboid1->frame.Rotate(1, glm::vec3(0, 0, 1));
   }


   if (_window->GetKeyState(GLFW_KEY_1) == GLFW_PRESS) {
       cuboid1->frame.Scale(0.999);
   }
   if (_window->GetKeyState(GLFW_KEY_2) == GLFW_PRESS) {
       cuboid1->frame.Scale(1.001);
   }
   

   

   if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS &&
       _window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
       auto v = _camera->frame.GetXAxis();
       v *= -0.005f;
       _camera->frame.Move(v);
   }
   if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS &&
       _window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
       auto v = _camera->frame.GetXAxis();
       v *= 0.005f;
       _camera->frame.Move(v);
   }
   if (_window->GetKeyState(GLFW_KEY_W) == GLFW_PRESS) {
       auto v = _camera->frame.GetZAxis();
       v *= -0.005f;
      _camera->frame.Move(v);
   }
   if (_window->GetKeyState(GLFW_KEY_S) == GLFW_PRESS) {
       auto v = _camera->frame.GetZAxis();
       v *= 0.005f;
       _camera->frame.Move(v);
   }
   
   if (_window->GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
      _camera->frame.Rotate(0.05f, _camera->frame.GetXAxis());
   }
   if (_window->GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
       _camera->frame.Rotate(-0.05f, _camera->frame.GetXAxis());
   }

   if (_window->GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
       _camera->frame.Rotate(0.05f, _camera->frame.GetYAxis());
   }
   if (_window->GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
       _camera->frame.Rotate(-0.05f, _camera->frame.GetYAxis());
   }

>>>>>>> Stashed changes
}


