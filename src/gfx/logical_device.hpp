#ifndef GFX_LOGICAL_DEVICE_HPP
#define GFX_LOGICAL_DEVICE_HPP

#include "gfx.hpp"
#include "physical_device.hpp"
#include "instance.hpp"

namespace gfx {

class LogicalDevice {
public:
    LogicalDevice(const Instance &instance, const PhysicalDevice &physicalDevice);

    ~LogicalDevice();
private:
    VkDevice handle;

    VkQueue graphicsQueue;
};

}

#endif