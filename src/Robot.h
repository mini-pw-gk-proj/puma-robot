//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_ROBOT_H
#define PUMAROBOT_ROBOT_H


#include "Shader.h"

class Robot {
public:
    void update(float timeMs);
    void render(Shader shader);
};


#endif //PUMAROBOT_ROBOT_H
