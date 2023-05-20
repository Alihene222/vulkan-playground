#ifndef GFX_LOGICAL_DEVICE_HPP
#define GFX_LOGICAL_DEVICE_HPP

#include "gfx.hpp"
#include "physical_device.hpp"
#include "instance.hpp"
#include "window_surface.hpp"

namespace gfx {

class LogicalDevice {
public:
    VkDevice handle;

    LogicalDevice(const Instance &instance, const PhysicalDevice &physicalDevice, WindowSurface *windowSurface);

    ~LogicalDevice();
private:
    VkQueue graphicsQueue;

    VkQueue presentQueue;

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
};

}

#endif