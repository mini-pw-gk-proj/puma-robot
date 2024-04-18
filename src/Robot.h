//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_ROBOT_H
#define PUMAROBOT_ROBOT_H


#include "Shader.h"
#include "mesh/Mesh.h"
#include "mesh/PositionVertex.h"

class Robot {

    std::unique_ptr<Mesh<PositionVertex>> mesh;

public:
    Robot();

    void update(float timeMs);
    void render(Shader &shader);
};


#endif //PUMAROBOT_ROBOT_H
