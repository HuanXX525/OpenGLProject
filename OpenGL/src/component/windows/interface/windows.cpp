#include <component/windows/main/main.h>
#include <component/windows/control/control.h>
#include <component/windows/interface/windows.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
namespace deluge_windows
{
    namespace deluge_windows_windows
    {
        Windows::Windows(){
            deluge_control::Control control;
            int test = control.Init();
        }
        Windows::~Windows(){
            
        }
        Windows* Windows::createWindows(char* title)
        {
            this->width = GetSystemMetrics(SM_CXFULLSCREEN);
            this->height = GetSystemMetrics(SM_CYFULLSCREEN);
            this->title = title;
            this->glfwWindow = glfwCreateWindow(static_cast<int>(width * 0.9), static_cast<int>(height * 0.9), title, NULL, NULL);
            return this;
        }
        Windows* Windows::redrawWindow(int width,int height)
        {
            // glViewport(0, 0, width, height);
            return this;
        }
        float Windows::screenWidth = 880.0f;
        float Windows::screenHeight = 660.0f;
    } // namespace deluge_windows_windows
} // namespace deluge_windows