#pragma once
#ifndef DELUGE_CONTROL
#define DELUGE_CONTROL
#include <glad.h>
#include <GLFW/glfw3.h> // Include GLFW header for GLFWwindow type

namespace deluge_windows
{
    namespace deluge_control
    {
        class Control
        {
        private:
            /* data */
        public:
            Control(/* args */);
            int Init();
            ~Control();
        };
        void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    } // namespace deluge_control
} // namespace deluge_windows

#endif