//
// Created by faliszewskii on 19.04.24.
//

#ifndef PUMAROBOT_APPCONTEXT_H
#define PUMAROBOT_APPCONTEXT_H


#include "../Robot.h"
#include "../camera/Camera.h"

struct AppContext {
    Robot robot;

    Camera camera;

    bool guiFocus = true;

    AppContext() : // TODO Remove fixed screen resolution
        camera(1920, 1080, CameraMode::ANCHOR, glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(0.f), glm::vec3(-M_PI/4,0,0))
        {}
};


#endif //PUMAROBOT_APPCONTEXT_H
