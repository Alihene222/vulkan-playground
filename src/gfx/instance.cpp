#include "instance.hpp"
#include "util.hpp"

using namespace gfx;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
    void* userData);

Instance::Instance(std::string name, bool validate) {
    this->validate = validate;

    VkApplicationInfo appInfo {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = name.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Volcano engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    const std::vector<const char*> extensions = getRequiredExtensions(validate);
    createInfo.enabledExtensionCount = static_cast<u32>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if(validate) {
        createInfo.enabledLayerCount = static_cast<u32>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo;
        fillDebugMessengerCreateInfo(debugMessengerCreateInfo);

        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugMessengerCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }
    
    if(vkCreateInstance(&createInfo, nullptr, &this->handle) != VK_SUCCESS) {
        std::cerr << "Instance creation failed" << std::endl;
        std::exit(-1);
    }
}

void Instance::destroy() {
    gfx::vkDestroyDebugUtilsMessengerEXT(this->handle, this->debugMessenger, nullptr);

    vkDestroyInstance(this->handle, nullptr);
}

void Instance::setupDebugMessgener() {
    if(validate) {
        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo;
        fillDebugMessengerCreateInfo(debugMessengerCreateInfo);

        if (gfx::vkCreateDebugUtilsMessengerEXT(this->handle, &debugMessengerCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
	        std::cerr << "Failed to set up debug messenger" << std::endl;
            std::exit(-1);
        }
    }
}

void Instance::fillDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

std::vector<const char*> Instance::getRequiredExtensions(bool validate) {
        uint32_t glfwExtensionCount = 0;
	    const char** glfwExtensions;
	    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	    if (validate) {
	        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	    }

	    return extensions;
    }

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
    void* userData) {

    std::cerr << "Validation layer: " << callbackData->pMessage << std::endl;

    return VK_FALSE;
}