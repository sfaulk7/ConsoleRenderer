#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Context.h"

bool aie::Context::Init(int Width, int Height, const char* Title)
{
    glfwInit();
    Window = glfwCreateWindow(640, 480, "Hello Window", nullptr, nullptr);
    glfwMakeContextCurrent(Window);

    glewInit();

    std::cout << "OpenGL Version: " << (const char*)glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << (const char*)glGetString(GL_VENDOR) << std::endl;
    std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    return false;
}

void aie::Context::Tick()
{
    glfwPollEvents();
    glfwSwapBuffers(Window);
}

void aie::Context::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void aie::Context::Term()
{
    glfwDestroyWindow(Window);
    glfwTerminate();
}

bool aie::Context::ShouldClose()
{
    return glfwWindowShouldClose(Window);
}

bool aie::Context::IsKeyDown(int key)
{
    return glfwGetKey(window, key);
}

glm::vec2 aie::Context::GetMousePosition()
{
    double x = 0;
    double y = 0;
    glfwGetCursorPos(window, &x, &y);

    return glm::vec2(x, y);
}

float aie::Context::GetAxis(int negativeKey, int positiveKey)
{
    float axis = 0.0f;

    if (IsKeyDown(negativeKey))
    {
        axis -= 1.0f;
    }
    if (IsKeyDown(positiveKey))
    {
        axis += 1.0f;
    }

    return axis;
}
