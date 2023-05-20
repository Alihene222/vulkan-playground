#ifndef GFX_PHYSICAL_DEVICE
#define GFX_PHYSICAL_DEVICE

#include "gfx.hpp"
#include "instance.hpp"
#include "window_surface.hpp"

namespace gfx {

class PhysicalDevice {
public:
    VkPhysicalDevice handle = VK_NULL_HANDLE;

    WindowSurface *windowSurface;

    PhysicalDevice(const Instance &instance, WindowSurface *windowSurface);

    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, WindowSurface *windowSurface);
private:
    bool isDeviceSuitable(VkPhysicalDevice device);

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};

}

#endif