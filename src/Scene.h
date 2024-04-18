//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_SCENE_H
#define PUMAROBOT_SCENE_H


#include "Robot.h"
#include "camera/Camera.h"

class Scene {

    Shader whiteShader;
    Shader phongShader;

    Robot robot;

public:
    Scene();
    void update();
    void render();

    Camera camera;
    bool guiFocus = true;
};


#endif //PUMAROBOT_SCENE_H
