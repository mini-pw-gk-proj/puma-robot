//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_ROBOT_H
#define PUMAROBOT_ROBOT_H


#include "Shader.h"
#include "mesh/Mesh.h"
#include "mesh/PositionVertex.h"

class Robot {

    Mesh<PositionVertex> mesh;

public:
    void update(float timeMs);
    void render(Shader shader);
};


#endif //PUMAROBOT_ROBOT_H
