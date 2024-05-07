//
// Created by faliszewskii on 07.05.24.
//

#ifndef PUMAROBOT_SPARKSENTITY_H
#define PUMAROBOT_SPARKSENTITY_H


#include "SparkGenerator.h"

class SparksEntity {
    SparkGenerator sparkGenerator;

public:
    void update();
    void render();
};


#endif //PUMAROBOT_SPARKSENTITY_H
