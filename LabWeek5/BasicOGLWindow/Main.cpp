#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "OpenGLGraphicsObject.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
    OpenGLGraphicsWindow* window =
        new OpenGLGraphicsWindow("Interactive Graphics Lab Week 5", 800, 600);
    window->backgroundColor = { 1.0f, 1.0f, 1.0f };

    // top triangle (1, 0.937, 0.239)
    // left (0.615, 1, 0.160)
    // right (0.996, 0.780, 0.886)

    OpenGLGraphicsObject* square = new OpenGLGraphicsObject();
    Vertex* squareVertices = new Vertex[6];
    squareVertices[0].x = 0.1f;
    squareVertices[0].y = 0.5f;
    squareVertices[0].z = 0.0f;
    squareVertices[0].red = 0.615f;
    squareVertices[0].green = 1.0f;
    squareVertices[0].blue = 0.160f;
  
    squareVertices[1].x = -0.1f;
    squareVertices[1].y = 0.5f;
    squareVertices[1].z = 0.0f;
    squareVertices[1].red = 0.615f;
    squareVertices[1].green = 1.0f;;
    squareVertices[1].blue = 0.160f;

    squareVertices[2].x = -0.1f;
    squareVertices[2].y = 0.0f;
    squareVertices[2].z = 0.0f;
    squareVertices[2].red = 0.615f;
    squareVertices[2].green = 1.0f;;
    squareVertices[2].blue = 0.160f;

    squareVertices[3].x = -0.1f;
    squareVertices[3].y = 0.0f;
    squareVertices[3].z = 0.0f;
    squareVertices[3].red = 0.996f;
    squareVertices[3].green = 0.780f;
    squareVertices[3].blue = 0.886f;

    squareVertices[4].x = 0.1f;
    squareVertices[4].y = 0.0f;
    squareVertices[4].z = 0.0f;
    squareVertices[4].red = 0.996f;
    squareVertices[4].green = 0.780f;
    squareVertices[4].blue = 0.886f;

    squareVertices[5].x = 0.1f;
    squareVertices[5].y = 0.5f;
    squareVertices[5].z = 0.0f;
    squareVertices[5].red = 0.996f;
    squareVertices[5].green = 0.780f;
    squareVertices[5].blue = 0.886f;
    square->SetObjectData(squareVertices, 6);


    OpenGLGraphicsObject* triangle = new OpenGLGraphicsObject();
    Vertex* triangleVertices = new Vertex[3];
    triangleVertices[0].x = 0.0f;
    triangleVertices[0].y = 1.0f;
    triangleVertices[0].z = 0.0f;
    triangleVertices[0].red = 1.0f;
    triangleVertices[0].green = 0.937f;
    triangleVertices[0].blue = 0.239f;

    triangleVertices[1].x = -0.2f;
    triangleVertices[1].y = 0.5f;
    triangleVertices[1].z = 0.0f;
    triangleVertices[1].red = 1.0f;
    triangleVertices[1].green = 0.937f;
    triangleVertices[1].blue = 0.239f;

    triangleVertices[2].x = 0.2f;
    triangleVertices[2].y = 0.5f;
    triangleVertices[2].z = 0.0f;
    triangleVertices[2].red = 1.0f;
    triangleVertices[2].green = 0.937f;
    triangleVertices[2].blue = 0.239f;
    triangle->SetObjectData(triangleVertices, 3);



    OpenGLGraphicsObject* object = new OpenGLGraphicsObject();
    Vertex* objectVertices = new Vertex[9];
    objectVertices[0] = squareVertices[0];
    objectVertices[1] = squareVertices[1];
    objectVertices[2] = squareVertices[2];
    objectVertices[3] = squareVertices[3];
    objectVertices[4] = squareVertices[4];
    objectVertices[5] = squareVertices[5];
    objectVertices[6] = triangleVertices[0];
    objectVertices[7] = triangleVertices[1];
    objectVertices[8] = triangleVertices[2];
    object->SetObjectData(objectVertices, 9);

    AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window);
    // graphics->setObject(square);
    graphics->setObject(object);


   graphics->InitializeContext();
   graphics->ShowWindow();
   graphics->Setup();
   graphics->Run();
   delete graphics;



   return 0;
}


