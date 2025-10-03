#pragma once

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

    };

}