#ifndef GFX_WINDOW_SURFACE_HPP
#define GFX_WINDOW_SURFACE_HPP

#include "gfx.hpp"
#include "window.hpp"
#include "instance.hpp"

namespace gfx {

class WindowSurface {
public:
    VkSurfaceKHR handle;

    WindowSurface(const Instance &instance, const gfx::Window &window);

    void destroy(const Instance &instance);
};

}

#endif