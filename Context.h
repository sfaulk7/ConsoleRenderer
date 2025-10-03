#pragma once

#include "glm/glm.hpp"

struct GLFWwindow;
namespace aie
{

    class Context
    {
        GLFWwindow* window = nullptr;

    public:
        GLFWwindow* Window = nullptr;
        bool Init(int Width, int Height, const char* Title);
        void Tick();
        void Clear();
        void Term();
        bool ShouldClose();

        bool IsKeyDown(int key);
        glm::vec2 GetMousePosition();
        float GetAxis(int negativeKey, int positiveKey);
    };

}