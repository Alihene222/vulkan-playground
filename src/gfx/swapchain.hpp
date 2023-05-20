#ifndef GFX_SWAPCHAIN_HPP
#define GFX_SWAPCHAIN_HPP

#include "gfx.hpp"
#include "physical_device.hpp"
#include "window.hpp"
#include "logical_device.hpp"

namespace gfx {

class SwapchainSupportDetails {
public:
    VkSurfaceCapabilitiesKHR capabilities;

    std::vector<VkSurfaceFormatKHR> formats;

    std::vector<VkPresentModeKHR> presentModes;
};

class Swapchain {
public:
    std::vector<VkImage> images;

    std::vector<VkImageView> imageViews;

    VkFormat format;

    VkExtent2D extent;

    Swapchain(PhysicalDevice *physicalDevice, LogicalDevice *logicalDevice, const Window &window);

    void destroy();

    static SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device, const WindowSurface &windowSurface);
private:
    VkSwapchainKHR handle;

    PhysicalDevice *physicalDevice;

    LogicalDevice *logicalDevice;

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availableModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, const Window &window);
};

}

#endif