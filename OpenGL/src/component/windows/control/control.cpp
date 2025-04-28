#include <component/windows/control/control.h>
#include <component/windows/interface/windows.h>

namespace deluge_windows
{
    namespace deluge_control
    {
        Control::Control(){

        }
        Control::~Control(){
            
        }
        int Control::Init(){
            return 1;
        }
        void framebuffer_size_callback(GLFWwindow *window, int width, int height)
        {
            deluge_windows::deluge_windows_windows::Windows *win = static_cast<deluge_windows::deluge_windows_windows::Windows *>(glfwGetWindowUserPointer(window));
            glViewport(0, 0, width, height);
            win->screenWidth = static_cast<float>(width);
            win->screenHeight = static_cast<float>(height);
        }
    } // namespace deluge_control
} // namespace deluge_windows
