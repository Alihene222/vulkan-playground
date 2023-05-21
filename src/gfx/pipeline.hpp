//Pipeline setup, FINALLY
#ifndef GFX_PIPELINE_HPP
#define GFX_PIPELINE_HPP

#include <vector>

#include "logical_device.hpp"
#include "swapchain.hpp"

namespace gfx {

class Pipeline {
public:
    Pipeline(LogicalDevice *logicalDevice, const Swapchain &swapchain);

    void destroy();

    void createShaderModules(std::string vertexPath, std::string fragmentPath);
private:
    VkPipelineLayout layout;

    LogicalDevice *logicalDevice;

    const std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkShaderModule vertexShader;
    
    VkShaderModule fragmentShader;
};

}

#endif