//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_ROBOT_H
#define PUMAROBOT_ROBOT_H


#include "Shader.h"
#include "mesh/Mesh.h"
#include "mesh/PositionNormalVertex.h"

class Robot {

    std::vector<Mesh<PositionNormalVertex>> meshes;

public:
    Robot();

    void update(float timeMs);
    void render(Shader &shader);

    Mesh<PositionNormalVertex> loadMesh(const std::string& path);
};


#endif //PUMAROBOT_ROBOT_H
