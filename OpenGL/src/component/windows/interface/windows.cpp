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
            if (!glfwInit())
            {
                this->returnMain = new int(-1); // 初始化失败
                return;
            }
            this->returnMain = new int(0);
            return;
        }
        Windows::~Windows(){
            
        }
        Windows* Windows::createWindows(char* title)
        {
            if(*(this->returnMain) == -1){
                return this;
            }
            this->width = GetSystemMetrics(SM_CXFULLSCREEN);
            this->height = GetSystemMetrics(SM_CYFULLSCREEN);
            this->title = title;
            this->glfwWindow = glfwCreateWindow(static_cast<int>(width * 0.9), static_cast<int>(height * 0.9), title, NULL, NULL);
            if (!this->glfwWindow)
            {
                glfwTerminate(); // 窗口创建失败
                this->returnMain = new int(-1);
            }
            this->initGlslVersion();
            this->makeContextCurrent();
            return this;
        }
        Windows* Windows::initGlslVersion(){
            if(*(this->returnMain) == -1){
                return this;
            }
            //版本
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            //核心渲染模式
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            return this;
        }
        Windows* Windows::makeContextCurrent(){
            if(*(this->returnMain) == -1){
                return this;
            }
            // 4. 设置当前上下文
            glfwMakeContextCurrent(this->glfwWindow);
            return this;
        }
        Windows* Windows::redrawWindow(int width,int height)
        {
            if(*(this->returnMain) == -1){
                return this;
            }
            // glViewport(0, 0, width, height);
            return this;
        }
        float Windows::screenWidth = 880.0f;
        float Windows::screenHeight = 660.0f;
    } // namespace deluge_windows_windows
} // namespace deluge_windows