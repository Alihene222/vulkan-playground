#include <vector>
#include <set>

#include "physical_device.hpp"
#include "swapchain.hpp"

using namespace gfx;

PhysicalDevice::PhysicalDevice(const Instance &instance, WindowSurface *windowSurface) {
    this->windowSurface = windowSurface;

    u32 deviceCount = 0;
    vkEnumeratePhysicalDevices(instance.handle, &deviceCount, nullptr);

    if(deviceCount == 0) {
        std::cerr << "No GPUs with Vulkan support available" << std::endl;
        std::exit(-1);
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance.handle, &deviceCount, devices.data());

    for(const auto &device : devices) {
        if(isDeviceSuitable(device)) {
            this->handle = device;
            break;
        }
    }

    if(this->handle == VK_NULL_HANDLE) {
        std::cerr << "Failed to find a suitable GPU" << std::endl;
        std::exit(-1);
    }
}

bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device, this->windowSurface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapchainAdequate = false;
    if (extensionsSupported) {
        SwapchainSupportDetails swapChainSupport = Swapchain::querySwapchainSupport(device, *this->windowSurface);
        swapchainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapchainAdequate;
}

QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkPhysicalDevice device, WindowSurface *windowSurface) {
    QueueFamilyIndices indices;

    u32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, windowSurface->handle, &presentSupport);

        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool PhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    u32 extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}