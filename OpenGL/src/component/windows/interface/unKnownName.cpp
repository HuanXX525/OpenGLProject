#include <component/windows/main/main.h>
#include <component/windows/control/control.h>
#include <component/windows/interface/what_is_the_best_namespace.h>
namespace deluge_windows
{
    namespace what_is_the_best_namespace
    {
        WhatIsTheBestNamespace::WhatIsTheBestNamespace(){
            deluge_control::Control control;
            int test = control.Init();
        }
        WhatIsTheBestNamespace::~WhatIsTheBestNamespace(){
            
        }
    } // namespace what_is_the_best_namespace
} // namespace what_is_the_best_namespace