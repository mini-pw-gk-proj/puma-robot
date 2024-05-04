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

public:
    explicit Gui(AppContext &appContext, GLFWwindow *window);

    void render();

    static void newFrame();

    ~Gui();

    void showSceneWindow();

    void pollEvents(ImVec2 canvas_sz);
};


#endif //PUMAROBOT_GUI_H
