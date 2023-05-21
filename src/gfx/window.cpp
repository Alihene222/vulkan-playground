#include "window.hpp"

gfx::Window::Window(std::string name, u16 width, u16 height, bool resizable) {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    this->handle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
}

void gfx::Window::destroy() {
    glfwDestroyWindow(this->handle);
    glfwTerminate();
}

bool gfx::Window::isCloseRequested() {
    return glfwWindowShouldClose(this->handle);
}