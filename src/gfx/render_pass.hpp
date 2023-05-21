#ifndef GFX_RENDER_PASS_HPP
#define GFX_RENDER_PASS_HPP

#include "logical_device.hpp"
#include "swapchain.hpp"

namespace gfx {

class RenderPass {
public:
    VkRenderPass handle;

    RenderPass(LogicalDevice *logicalDevice, const Swapchain &swapchain);

    void destroy();
private:
    LogicalDevice *logicalDevice;
};

}

#endif