#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLGraphicsObject.h"
#include "OpenGLVertexPCTStrategy.h"

OpenGLGraphicsSystem::OpenGLGraphicsSystem() :
   AbstractGraphicsSystem()
{
   _window = new OpenGLGraphicsWindow("OpenGL Window", 800, 600);
}

OpenGLGraphicsSystem::OpenGLGraphicsSystem(
   OpenGLGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer) :
   AbstractGraphicsSystem(window, camera, timer)
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
   bool shaderNotCreated = false;
   for (auto shaderIter = _shaders.begin(); shaderIter != _shaders.end(); shaderIter++) {
      auto shader = shaderIter->second;
      if (!shader->Create()) {
         _errorReport += shader->ReportErrors();
         shaderNotCreated = true;
      }
   }
   if (shaderNotCreated) return false;
   return true;
}

void OpenGLGraphicsSystem::ShowWindow()
{
   _window->SetOnResize();
   _window->ShowMaximized();
}

void OpenGLGraphicsSystem::Setup()
{
   // Cull back faces and use counter-clockwise winding of front faces
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);

   // Enable depth testing
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glDepthFunc(GL_LEQUAL);
   glDepthRange(0.0f, 1.0f);

   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Setup();
   }
}

void OpenGLGraphicsSystem::Run()
{
   float S = 0;
   double elapsedSeconds;
   _timer->StartTiming();
   while (!_window->IsTimeToClose()) {
      elapsedSeconds = _timer->GetElapsedTimeInSeconds();
      ProcessInput();
      
      _camera->SetupLookingForward();
      _camera->SetupProjectionAndView(_window->GetAspectRatio());
      for (auto shaderIter = _shaders.begin(); shaderIter != _shaders.end(); shaderIter++) {
         auto shader = (GLSLGraphicsShader*)shaderIter->second;
         shader->projection = _camera->GetProjection();
         shader->view = _camera->GetView();
      }
      
      auto strategy = (OpenGLVertexPCTStrategy*)_objects["sky"]->vertexStrategy;
      strategy->SetTextureCoord(0, S, 1.0f);
      strategy->SetTextureCoord(1, S, 0.0f);
      strategy->SetTextureCoord(2, 1.0f + S, 0.0f);
      strategy->SetTextureCoord(3, S, 1.0f);
      strategy->SetTextureCoord(4, 1.0f + S, 0.0f);
      strategy->SetTextureCoord(5, 1.0f + S, 1.0f);
      strategy->SelectVAO();
      strategy->SetupBuffer();
      S += (float)(0.05f * elapsedSeconds);
      if (S > 1.0f) S = 0;


      _camera->Update(elapsedSeconds);
      _window->Clear();

      for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
          iterator->second->Update(elapsedSeconds);
      }

      for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
         iterator->second->Render();
      }

      _window->SwapBuffers();
   }
}

void OpenGLGraphicsSystem::ProcessInput()
{
   if (_window->GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      _window->Close();
   }
   auto cube = (OpenGLGraphicsObject*)_objects["Cube"];
   auto c2 = (OpenGLGraphicsObject*)_objects["C2"];
   if (_window->GetKeyState(GLFW_KEY_Y) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(0, 1, 0));
      c2->frame.RotateWorld(1, glm::vec3(0, 1, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_X) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(1, 0, 0));
      c2->frame.RotateWorld(1, glm::vec3(1, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_Z) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(0, 0, 1));
      c2->frame.RotateWorld(1, glm::vec3(0, 0, 1));
   }
   if (_window->GetKeyState(GLFW_KEY_R) == GLFW_PRESS) {
      cube->frame.Reset();
      c2->frame.Reset();
   }
   if (_window->GetKeyState(GLFW_KEY_1) == GLFW_PRESS) {
      c2->frame.Scale(0.9f);
   }
   if (_window->GetKeyState(GLFW_KEY_2) == GLFW_PRESS) {
      c2->frame.Scale(1.1f);
   }

   if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS) {
      if (_window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
         _camera->SetState(BaseCamera::CameraState::MovingRight);
      }
      else {
         _camera->SetState(BaseCamera::CameraState::TurningRight);
      }
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS) {
      if (_window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
         _camera->SetState(BaseCamera::CameraState::MovingLeft);
      }
      else {
         _camera->SetState(BaseCamera::CameraState::TurningLeft);
      }
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_W) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingForward);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_S) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingBackward);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingUp);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingDown);
      return;
   }
   _camera->SetState(BaseCamera::CameraState::NotMoving);

}


