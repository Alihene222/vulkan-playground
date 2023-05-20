#include <iostream>

#include "gfx/instance.hpp"
#include "gfx/window.hpp"
#include "gfx/physical_device.hpp"
#include "gfx/logical_device.hpp"
#include "gfx/window_surface.hpp"
#include "gfx/swapchain.hpp"

int main() {
    gfx::Window window("Hello, World!", 640, 640, false);
    gfx::Instance instance("Hello, World!", true);
    instance.setupDebugMessgener();
    gfx::WindowSurface windowSurface(instance, window);
    gfx::PhysicalDevice physicalDevice(instance, &windowSurface);
    gfx::LogicalDevice logicalDevice(instance, physicalDevice, &windowSurface);
    gfx::Swapchain swapchain(&physicalDevice, &logicalDevice, window);

    while(!window.isCloseRequested()) {
        glfwPollEvents();
    }

    swapchain.destroy();
    windowSurface.destroy(instance);
    
    return 0;
}