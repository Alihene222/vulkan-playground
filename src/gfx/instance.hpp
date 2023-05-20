#ifndef GFX_INSTANCE_HPP
#define GFX_INSTANCE_HPP

#include <iostream>
#include <vector>

#include "gfx.hpp"

namespace gfx {

class Instance {
public:
    VkInstance handle;

    bool validate;

    VkDebugUtilsMessengerEXT debugMessenger;

    Instance(std::string name, bool validate);
    
    ~Instance();

    static void fillDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
private:
    const std::vector<const char*> validationLayers = {
	    "VK_LAYER_KHRONOS_validation"
    };

    std::vector<const char*> getRequiredExtensions(bool validate);
};

}

#endif