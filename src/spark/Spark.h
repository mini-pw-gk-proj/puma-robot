//
// Created by faliszewskii on 07.05.24.
//

#ifndef PUMAROBOT_SPARK_H
#define PUMAROBOT_SPARK_H

#include <glm/vec3.hpp>

struct Spark {
    glm::vec3 prevPos;
    glm::vec3 currPos;
    glm::vec3 velocity;
    float ttl;
};

#endif //PUMAROBOT_SPARK_H
