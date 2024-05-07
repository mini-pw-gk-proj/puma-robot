//
// Created by faliszewskii on 07.05.24.
//

#ifndef PUMAROBOT_SPARKSENTITY_H
#define PUMAROBOT_SPARKSENTITY_H


#include "SparkGenerator.h"
#include "../mesh/SparkVertex.h"

class SparksEntity {
    Mesh<SparkVertex> mesh;
    SparkGenerator sparkGenerator;

public:
    explicit SparksEntity(Robot &robot) :
        mesh({}, {}, GL_POINTS),
        sparkGenerator(robot) {}

    void update();
    void render(Shader &shader);
};


#endif //PUMAROBOT_SPARKSENTITY_H
