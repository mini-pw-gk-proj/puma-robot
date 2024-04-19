//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_SCENE_H
#define PUMAROBOT_SCENE_H


#include "Robot.h"
#include "camera/Camera.h"
#include "app/AppContext.h"

class Scene {

    Shader whiteShader;
    Shader phongShader;

    AppContext &appContext;

public:
    explicit Scene(AppContext &appContext);
    void update();
    void render();
};


#endif //PUMAROBOT_SCENE_H
