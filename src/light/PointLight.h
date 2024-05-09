//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_POINTLIGHT_H
#define PUMAROBOT_POINTLIGHT_H

#include "../Shader.h"

struct PointLight {

    glm::vec3 position = glm::vec3(-1.3, 0, 1);
    glm::vec3 color = glm::vec3(255/255.f, 214/255.f, 170/255.f);
    float strength = 1.f;
    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.7f;
    float quadraticAttenuation = 1.8f;
    int chosenLight = 1;

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
