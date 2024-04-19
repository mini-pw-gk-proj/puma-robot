//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_GUI_H
#define PUMAROBOT_GUI_H


#include "GLFW/glfw3.h"

class Gui {
public:
    explicit Gui(GLFWwindow *window);

    void render();

    void newFrame();

    ~Gui();
};


#endif //PUMAROBOT_GUI_H
