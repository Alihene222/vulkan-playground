#include <iostream>

#include "gfx/instance.hpp"
#include "gfx/window.hpp"

int main() {
    gfx::Window window("Hello, World!", 640, 640, false);
    gfx::Instance instance("Hello, World!", true);

    while(!window.isCloseRequested()) {
        glfwPollEvents();
    }
    
    return 0;
}