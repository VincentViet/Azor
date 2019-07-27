//
// Created by vice on 24/07/2019.
//

#ifndef AZOR_SRC_WINDOW_WINDOW_H_
#define AZOR_SRC_WINDOW_WINDOW_H_

#include <tinyxml2.h>

struct GLFWwindow;

namespace window{

    enum class Keys{
        RIGHT = 262,
        LEFT = 263,
        DOWN = 264,
        UP = 265,
        X = 88
    };

    void    startUp(tinyxml2::XMLElement* window_node);
    void    shutdown();
    void    update();
    int     getWidth();
    int     getHeight();
    double  getDeltaTime();
    bool    isClosed();

    GLFWwindow* getWindow();

    bool    isKeyDown(Keys k);
    bool    isKeyUp(Keys k);
}

#endif //AZOR_SRC_WINDOW_WINDOW_H_
