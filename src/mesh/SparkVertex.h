//
// Created by faliszewskii on 07.05.24.
//

#ifndef PUMAROBOT_SPARKVERTEX_H
#define PUMAROBOT_SPARKVERTEX_H


#include "../glew_glfw.h"
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct SparkVertex{
    glm::vec3 prevPos;
    glm::vec3 nextPos;
    glm::vec3 tangent;
    float ttl;

    inline static std::vector<int> getSizes() { return {3, 3, 3, 1}; }
    inline static std::vector<int> getTypes() { return {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT}; }
    inline static std::vector<int> getOffsets() { return {0, offsetof(SparkVertex, nextPos), offsetof(SparkVertex, tangent), offsetof(SparkVertex, ttl)}; }
};

#endif //PUMAROBOT_SPARKVERTEX_H
