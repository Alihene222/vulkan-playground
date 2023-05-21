#include <iostream>

#include "gfx/instance.hpp"
#include "gfx/window.hpp"
#include "gfx/physical_device.hpp"
#include "gfx/logical_device.hpp"
#include "gfx/window_surface.hpp"
#include "gfx/swapchain.hpp"
#include "gfx/pipeline.hpp"
#include "gfx/render_pass.hpp"

int main() {
    gfx::Window window("Hello, World!", 640, 640, false);
    gfx::Instance instance("Hello, World!", true);
    instance.setupDebugMessgener();
    gfx::WindowSurface windowSurface(instance, window);
    gfx::PhysicalDevice physicalDevice(instance, &windowSurface);
    gfx::LogicalDevice logicalDevice(instance, physicalDevice, &windowSurface);
    gfx::Swapchain swapchain(&physicalDevice, &logicalDevice, window);
    gfx::Pipeline pipeline(&logicalDevice, swapchain);
    pipeline.createShaderModules("bin/shaders/coreVert.spv", "bin/shaders/coreFrag.spv");
    gfx::RenderPass renderPass(&logicalDevice, swapchain);

    while(!window.isCloseRequested()) {
        glfwPollEvents();
    }

    pipeline.destroy();
    renderPass.destroy();
    swapchain.destroy();
    windowSurface.destroy(instance);
    logicalDevice.destroy();
    instance.destroy();
    window.destroy();
    
    return 0;
}