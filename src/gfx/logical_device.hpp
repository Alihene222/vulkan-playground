#ifndef GFX_LOGICAL_DEVICE_HPP
#define GFX_LOGICAL_DEVICE_HPP

#include "gfx.hpp"
#include "physical_device.hpp"
#include "instance.hpp"
#include "window_surface.hpp"

namespace gfx {

class LogicalDevice {
public:
    LogicalDevice(const Instance &instance, const PhysicalDevice &physicalDevice, WindowSurface *windowSurface);

    ~LogicalDevice();
private:
    VkDevice handle;

    VkQueue graphicsQueue;

    VkQueue presentQueue;
};

}

#endif