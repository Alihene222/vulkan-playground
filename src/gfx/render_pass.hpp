#ifndef GFX_RENDER_PASS_HPP
#define GFX_RENDER_PASS_HPP

#include "logical_device.hpp"
#include "swapchain.hpp"

namespace gfx {

class RenderPass {
public:
    RenderPass(LogicalDevice *logicalDevice, const Swapchain &swapchain);

    void destroy();
private:
    VkRenderPass handle;

    LogicalDevice *logicalDevice;
};

}

#endif