//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_POINTLIGHT_H
#define PUMAROBOT_POINTLIGHT_H

#include "../Shader.h"

struct PointLight {

    glm::vec3 position = glm::vec3(0, 2, 1);
    glm::vec3 color = glm::vec3(1.0f);
    float strength = 4.0f;
    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.7f;
    float quadraticAttenuation = 1.8f;

    void setupPointLight(Shader& shader) {
        shader.setUniform("pointLight.position", position);
        shader.setUniform("pointLight.color", color);
        shader.setUniform("pointLight.strength", strength);
        shader.setUniform("pointLight.constantAttenuation", constantAttenuation);
        shader.setUniform("pointLight.linearAttenuation", linearAttenuation);
        shader.setUniform("pointLight.quadraticAttenuation", quadraticAttenuation);
    }
};

#endif //PUMAROBOT_POINTLIGHT_H
