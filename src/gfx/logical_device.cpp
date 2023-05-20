#include "logical_device.hpp"

using namespace gfx;

LogicalDevice::LogicalDevice(const Instance &instance, const PhysicalDevice &physicalDevice) {
    QueueFamilyIndices indices = PhysicalDevice::findQueueFamilies(physicalDevice.handle);

    VkDeviceQueueCreateInfo queueCreateInfo {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    f32 queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures {};
    
    VkDeviceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

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
}

LogicalDevice::~LogicalDevice() {
    vkDestroyDevice(this->handle, nullptr);
}