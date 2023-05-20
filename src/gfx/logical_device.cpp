#include <set>

#include "logical_device.hpp"

using namespace gfx;

LogicalDevice::LogicalDevice(const Instance &instance, const PhysicalDevice &physicalDevice, WindowSurface *windowSurface) {
    QueueFamilyIndices indices = PhysicalDevice::findQueueFamilies(physicalDevice.handle, windowSurface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<u32> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    f32 queuePriority = 1.0f;
    for(u32 queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures {};
    
    VkDeviceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<u32>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<u32>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if(instance.validate) {
        createInfo.enabledLayerCount = static_cast<u32>(instance.validationLayers.size());
        createInfo.ppEnabledLayerNames = instance.validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice.handle, &createInfo, nullptr, &this->handle) != VK_SUCCESS) {
        std::cerr << "Failed to create logical device" << std::endl;
        std::exit(-1);
    }

    vkGetDeviceQueue(this->handle, indices.graphicsFamily.value(), 0, &this->graphicsQueue);
    vkGetDeviceQueue(this->handle, indices.presentFamily.value(), 0, &this->presentQueue);
}

LogicalDevice::~LogicalDevice() {
    vkDestroyDevice(this->handle, nullptr);
}