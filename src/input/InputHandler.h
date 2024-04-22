//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_INPUTHANDLER_H
#define PUMAROBOT_INPUTHANDLER_H

#include <functional>
#include "../Scene.h"

class InputHandler {
    AppContext &appContext;
public:
    explicit InputHandler(AppContext &appContext) : appContext(appContext) {};

    void setupCallbacks(GLFWwindow *window);

private:
    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) const;
    void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    void mouseCallback(GLFWwindow *window, double xposIn, double yposIn);
    void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    void windowResize(GLFWwindow* window, int width, int height);
};




#endif //PUMAROBOT_INPUTHANDLER_H
