#include <vector>

#include "physical_device.hpp"

using namespace gfx;

PhysicalDevice::PhysicalDevice(const Instance &instance) {
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
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.isComplete();
}

QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    u32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}