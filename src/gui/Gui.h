//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_GUI_H
#define PUMAROBOT_GUI_H


#include "../app/AppContext.h"
#include "imgui.h"

class Gui {
    AppContext &appContext;

    void showScene();

    void updateCameraPos(ImVec2 canvas_sz);

public:
    explicit Gui(AppContext &appContext, GLFWwindow *window);

    void render();

    static void newFrame();

    ~Gui();

    void showSceneWindow();
};


#endif //PUMAROBOT_GUI_H
