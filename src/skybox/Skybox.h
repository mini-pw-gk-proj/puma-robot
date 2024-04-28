//
// Created by faliszewskii on 28.04.24.
//

#ifndef PUMAROBOT_SKYBOX_H
#define PUMAROBOT_SKYBOX_H


#include <memory>
#include "../mesh/PositionVertex.h"
#include "../mesh/Mesh.h"

class Skybox {
    std::unique_ptr<Mesh<PositionVertex>> mesh;
    unsigned int textureId;
    const static unsigned int SKYBOX_SIZE = 500;

public:
    Skybox();

    void render();

    void setupCubemap();

    static std::vector<PositionVertex> getVertices() ;
};


#endif //PUMAROBOT_SKYBOX_H
