#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"
#include "GraphicsObjectReader.h"
#include "Generate.h"

void ReportError(const string& error) 
{
   // Quick way to convert from string to wstring
   wstring errorString(error.begin(), error.end());
   MessageBox(
      NULL,
      errorString.c_str(),
      L"An Error Occurred",
      MB_OK);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   OpenGLGraphicsWindow* window = 
      new OpenGLGraphicsWindow("Interactive Graphics Lab Week 6");
   window->backgroundColor = { 0.5f, 0.0f, 0.5f };

   OpenGLGraphicsObject* rectangle = nullptr;
   GraphicsObjectReader reader("rectangle.ig");
   if (reader.Read()) {
      rectangle = reader.GetObject();
   }
   else {
      ReportError(reader.ReportErrors());
      return 0;
   }

   GLSLGraphicsShader* shader = 
      new GLSLGraphicsShader(new TextFileReader());
   if (!shader->ReadShaderSources(
      "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(shader->ReportErrors());
      return 0;
   }
<<<<<<< Updated upstream
   rectangle->SetShader(shader);

   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, shader);
   graphics->SetObject(rectangle);
=======
   object->SetShader(shader);

   auto camera = new BaseCamera();
   camera->frame.SetPosition(0.0f, 1.0f, 7.0f);
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, shader);

   graphics->AddObject("Cube", object);

   object = Generate::FlatSurface(10, 10, { 0.0f, 0.5f, 0.0f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("Floor", object);


   object = Generate::Cuboid(1, 2, 1.5, { 0.50f, 0.50f, 0.0f, 1.0f });
    object->SetColor(0, 6, { 1.0f, 0.0f, 0.0f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("Cuboid1", object);

   object = Generate::Cuboid(0.5, 1.4, 1.0, { 0.0f, 0.50f, 0.50f, 1.0f });
   object->SetColor(4, 6, { 0.0f, 0.0f, 1.0f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("Cuboid2", object);




   auto cube = (OpenGLGraphicsObject*)graphics->GetObject("Cube");
   cube->frame.Move({ 0.0f, 0.5f, 0.0f });

   auto cuboid1 = (OpenGLGraphicsObject*)graphics->GetObject("Cuboid1");
   cuboid1->frame.Move({ 1.5f, 0.5f, 1.5f });

   auto cuboid2 = (OpenGLGraphicsObject*)graphics->GetObject("Cuboid2");
   cuboid2->frame.Move({ -1.5f, 0.5f, 2.5f });


>>>>>>> Stashed changes
   if (graphics->InitializeContext()) {
      graphics->ShowWindow();
      graphics->Setup();
      graphics->Run();
   }
   else {
      ReportError(graphics->ReportErrors());
   }
   delete graphics;
   return 0;
}