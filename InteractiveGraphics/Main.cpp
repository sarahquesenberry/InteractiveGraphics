#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"
#include "GraphicsObjectReader.h"
#include "Generate.h"
#include "HighResolutionTimer.h"
#include "OpenGLVertexPCStrategy.h"
#include "OpenGLTexture.h"
#include "RotateAnimation.h"

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
      new OpenGLGraphicsWindow("Interactive Graphics Lab Week 8");



   GLSLGraphicsShader* simple3DShader = new GLSLGraphicsShader(new TextFileReader());
   if (!simple3DShader->ReadShaderSources(
      "Simple3DVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(simple3DShader->ReportErrors());
      return 0;
   }
   GLSLGraphicsShader* simplePCTShader = new GLSLGraphicsShader(new TextFileReader());
   if (!simplePCTShader->ReadShaderSources(
      "VSPositionColorTexture.glsl", "FSPositionColorTexture.glsl")) {
      ReportError(simplePCTShader->ReportErrors());
      return 0;
   }

   auto timer = new HighResolutionTimer();
   auto camera = new BaseCamera();
   camera->frame.SetPosition(2.0f, 3.0f, 10.0f);
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, timer);
   graphics->AddShader("Simple3DShader", simple3DShader);
   graphics->AddShader("SimplePCTShader", simplePCTShader);

   OpenGLGraphicsObject* cubeFromFile = nullptr;
   GraphicsObjectReader reader("cube.ig");
   if (reader.Read()) {
      cubeFromFile = reader.GetGraphicsObject();
   }
   else {
      ReportError(reader.ReportErrors());
      return 0;
   }
   graphics->AddObject("Cube", cubeFromFile, "Simple3DShader");

    

   auto cube = (OpenGLGraphicsObject*)graphics->GetGraphicsObject("Cube");
   cube->frame.Move({ 0.0f, 0.5f, 0.0f });

   OpenGLGraphicsObject* object = Generate::Cuboid(0.5f, 1, 1, { 0.5f, 0.5f, 0.0f, 1.0f });
   graphics->AddObject("C2", object, "Simple3DShader");
   object->frame.Move({ 3.0f, 0.5f, 0.0f });
   auto c2 = (OpenGLGraphicsObject*)graphics->GetGraphicsObject("C2");
   auto vertexStrategy = (OpenGLVertexPCStrategy*)c2->vertexStrategy;
   vertexStrategy->SetColor(0, 6, { 0.5f, 0.0f, 0.0f, 1.0f });

   object = Generate::Cuboid(1, 2, 1, { 0.0f, 0.5f, 0.5f, 1.0f });
   graphics->AddObject("C3", object, "Simple3DShader");
   object->frame.Move({ 0.0f, 0.5f, 4.0f });
   auto c3 = (OpenGLGraphicsObject*)graphics->GetGraphicsObject("C3");
   vertexStrategy = (OpenGLVertexPCStrategy*)c3->vertexStrategy;
   vertexStrategy->SetColor(0, 6, { 0.5f, 0.0f, 0.0f, 1.0f });

   OpenGLTexture* wallTexture = new OpenGLTexture();
   //unsigned char pixels[] = {
   //  128,   0,   0, 139,  69,  19, 0, 0, // Bottom of image
   //  139,  69,  19, 188, 143, 143, 0, 0
   //};
   //wallTexture->LoadFromArray(pixels, 16, 2, 2);
   wallTexture->LoadFromFile("brickwall.jpg");
   wallTexture->SetMagFilter(GL_LINEAR);
   wallTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("brickwall", wallTexture);

   OpenGLGraphicsObject* wall = Generate::TexturedFlatSurface(10, 10, { 1.0f, 1.0f, 1.0f, 1.0f }, 5.0f, 5.0f);
   wall->SetTexture(wallTexture);
   graphics->AddObject("wall", wall, "SimplePCTShader");
   wall->frame.Move({ 0.0f, 5.0f, -5.0f });
   wall->frame.Rotate(90.0f, wall->frame.GetXAxis());

   OpenGLTexture* floorTexture = new OpenGLTexture();
   unsigned char pixels[] = {
     75, 0, 130, 255,  0,  255, 0, 0, // Bottom of image
     255,  0,  255, 75, 0, 130, 0, 0
   };
   floorTexture->LoadFromArray(pixels, 16, 2, 2);
   graphics->AddTexture("checkeredFloor", floorTexture);

   OpenGLGraphicsObject* floor = Generate::TexturedFlatSurface(50, 50, { 1.0f, 1.0f, 1.0f, 1.0f }, 50.0, 50.0);
   floor->SetTexture(floorTexture);
   graphics->AddObject("floor", floor, "SimplePCTShader");


   OpenGLTexture* crateTexture = new OpenGLTexture();
   crateTexture->LoadFromFile("crate.jpg");
   graphics->AddTexture("C3", crateTexture);

   
   OpenGLGraphicsObject* crate = Generate::TexturedCuboid(3, 3, 3, { 1.0, 1.0, 1.0, 1.0 });
   crate->SetTexture(crateTexture);
   graphics->AddObject("crate", crate, "SimplePCTShader");
   crate->frame.Move({-3.0f, 2.0f, 0.0f});

   auto rotateAnimation = new RotateAnimation();
   rotateAnimation->graphicsObject = graphics->GetGraphicsObject("crate");
   graphics->GetGraphicsObject("crate")->animation = rotateAnimation;



   OpenGLTexture* skyTexture = new OpenGLTexture();
   skyTexture->LoadFromFile("sky.jpg");
   skyTexture->SetMagFilter(GL_LINEAR);
   skyTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("sky", skyTexture);

   OpenGLGraphicsObject* sky = Generate::TexturedFlatSurface(100, 100, { 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f);
   sky->SetTexture(skyTexture);
   graphics->AddObject("sky", sky, "SimplePCTShader");
   sky->frame.Move({ 0.0f, 15.0f, 0.0f });
   sky->frame.Rotate(180.0f, wall->frame.GetXAxis());




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