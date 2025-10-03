#include "Context.h"
#include "ConsoleRenderer.h"

#include <GLFW/glfw3.h> // for glfwGetTime()

#include "Transform.h"
#include "Object.h"
#include "Camera.h"

using namespace aie;

int main()
{
    Context Window;
    Window.Init(640, 480, "Hello Window");


    Geometry LoadSpear = LoadGeometry("ConsoleRenderer/Res/SampleAssets/obj/soulspear.obj");
    Texture SpearTex = LoadTexture("ConsoleRenderer/Res/SampleAssets/img/soulspear_diffuse.tga");

    //Shader basicShad = MakeShader(.vert, .frag);
    //Geometry basicTriangleGeo = MakeGeometry(triVerts, 3, triIndices, 3);
    //Shader basicShaderFromFile = LoadShader("ConsoleRenderer/Res/Shaders/Basic.vert", "ConsoleRenderer/Res/Shaders/Basic.frag");
    //Shader cameraShaderFromFile = LoadShader("ConsoleRenderer/Res/Shaders/BasicCamera.vert", "ConsoleRenderer/Res/Shaders/Basic.frag");
    Shader texShaderFromFile = LoadShader("ConsoleRenderer/Res/Shaders/BasicCamera.vert", "ConsoleRenderer/Res/Shaders/Tex.frag");

    Texture Jack = LoadTexture("ConsoleRenderer/Res/Textures/Jamsepticeye.PNG");

    //Model Matrix - transform object to WORLD space
    glm::mat4 triangle_model = glm::identity<glm::mat4>();

    //View Matrix - makes things RELATIVE to the camera
    glm::mat4 cam_view = 
        glm::lookAt(
        glm::vec3(0, 5, 20), // eye
        glm::vec3(0, 5, 0),  // look at position
        glm::vec3(0, 1, 0)); // up direction
 
    //Projection Matrix - transforms View Space into Clip Space ( -1 to +1 zone)
    glm::mat4 cam_proj = 
        glm::perspective(
            glm::radians(45.f), //FOV
            640.0f / 480.0f, // Aspect Ratio
            0.1f, //Near-Plane
            1000.0f); //Far-Plane

    // define ambient color
    glm::vec3 ambient(2.0f, 2.0f, 2.0f);
    // NEW: define sun direction
    glm::vec3 sunDirection(1, 0, 1);
    glm::vec3 sunDirection2(2, 0, 2);

    while (!Window.ShouldClose())
    {
        Window.Tick();
        Window.Clear();

        SetUniform(texShaderFromFile, 0, cam_proj);           // projection mat
        SetUniform(texShaderFromFile, 1, cam_view);           // view mat
        SetUniform(texShaderFromFile, 2, triangle_model);     // model mat

        SetUniform(texShaderFromFile, 3, SpearTex, 0);        // albedo (main color or texture)
        SetUniform(texShaderFromFile, 4, ambient);            // ambient light
        SetUniform(texShaderFromFile, 5, sunDirection);       // NEW: directional light
        SetUniform(texShaderFromFile, 6, glm::vec3(0, 0, 255)); // Light Color
        SetUniform(texShaderFromFile, 7, sunDirection2);       // NEW: directional light
        SetUniform(texShaderFromFile, 8, glm::vec3(255, 0, 0)); // Light Color


        Draw(texShaderFromFile, LoadSpear);
    }

    FreeGeometry(LoadSpear);

    FreeShader(texShaderFromFile);

    Window.Term();

    return 0;
}