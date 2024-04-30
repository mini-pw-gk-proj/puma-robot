//
// Created by faliszewskii on 30.04.24.
//

#ifndef PUMAROBOT_MATERIAL_H
#define PUMAROBOT_MATERIAL_H

#include "glm/vec3.hpp"
#include "../Shader.h"

struct Material {
    glm::vec4 albedo;
    float roughness;
    float metallic;

    void setupMaterial(Shader& shader) {
        shader.setUniform("material.albedo", albedo);
        shader.setUniform("material.roughness", roughness);
        shader.setUniform("material.metallic", metallic);
    }
};
#endif //PUMAROBOT_MATERIAL_H
