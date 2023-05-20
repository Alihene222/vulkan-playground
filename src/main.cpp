#include <iostream>

#include "gfx/instance.hpp"
#include "gfx/window.hpp"
#include "gfx/physical_device.hpp"
#include "gfx/logical_device.hpp"

int main() {
    gfx::Window window("Hello, World!", 640, 640, false);
    gfx::Instance instance("Hello, World!", true);
    gfx::PhysicalDevice physicalDevice(instance);
    gfx::LogicalDevice logicalDevice(instance, physicalDevice);

    while(!window.isCloseRequested()) {
        glfwPollEvents();
    }
    
    return 0;
}