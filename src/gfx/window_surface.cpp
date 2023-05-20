#include "window_surface.hpp"

using namespace gfx;

WindowSurface::WindowSurface(const Instance &instance, const gfx::Window &window) {
    if (glfwCreateWindowSurface(instance.handle, window.handle, nullptr, &this->handle) != VK_SUCCESS) {
        std::cerr << "Failed to create window surface" << std::endl;
        std::exit(-1);
    }
}

void WindowSurface::destroy(const Instance &instance) {
    vkDestroySurfaceKHR(instance.handle, this->handle, nullptr);
}