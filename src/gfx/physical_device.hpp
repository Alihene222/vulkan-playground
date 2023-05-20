#ifndef GFX_PHYSICAL_DEVICE
#define GFX_PHYSICAL_DEVICE

#include "gfx.hpp"
#include "instance.hpp"

namespace gfx {

class PhysicalDevice {
public:
    VkPhysicalDevice handle = VK_NULL_HANDLE;

    PhysicalDevice(const Instance &instance);

    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
private:
    bool isDeviceSuitable(VkPhysicalDevice device);
};

}

#endif