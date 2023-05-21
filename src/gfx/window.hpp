#ifndef GFX_WINDOW_HPP
#define GFX_WINDOW_HPP

#include <iostream>

#include "gfx.hpp"
#include "util.hpp"

namespace gfx {

class Window {
public:
    GLFWwindow *handle;

    Window(std::string name, u16 width, u16 height, bool resizable);

    void destroy();

    bool isCloseRequested();
};

}

#endif