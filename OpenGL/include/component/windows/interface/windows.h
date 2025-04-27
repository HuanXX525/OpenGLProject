#pragma once
#include <component/windows/main/main.h>
#include <component/windows/control/control.h>
#include <GLFW/glfw3.h>
#ifndef DELUGE_WINDOWS
#define DELUGE_WINDOWS
namespace deluge_windows
{
    namespace deluge_windows_windows
    {
        class Windows
        {
        private:
            /* data */
            char* title;
            Windows* initGlslVersion();
            Windows* makeContextCurrent();
        public:
            int width;
            int height;
            static float screenWidth;
            static float screenHeight;
            GLFWwindow* glfwWindow;
            int* returnMain;
            Windows(/* args */);
            ~Windows();
            Windows* createWindows(char* title);
            Windows* redrawWindow(int width,int height);
        };
    } // namespace deluge_windows_windows
} // namespace deluge_windows
#endif