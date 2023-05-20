#ifndef GFX_PHYSICAL_DEVICE
#define GFX_PHYSICAL_DEVICE

#include "gfx.hpp"
#include "instance.hpp"

namespace gfx {

class PhysicalDevice {
public:
    PhysicalDevice(const Instance &instance);
private:
    VkPhysicalDevice handle = VK_NULL_HANDLE;

    bool isDeviceSuitable(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

}

#endif