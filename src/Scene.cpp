//
// Created by faliszewskii on 18.04.24.
//

#include "Scene.h"


Scene::Scene() : // TODO Remove fixed screen resolution
        whiteShader("../res/shaders/basic/position.vert", "../res/shaders/basic/white.frag"),
        phongShader("../res/shaders/phong/phong.vert", "../res/shaders/phong/phong.frag"),
        camera(1920, 1080, CameraMode::ANCHOR, glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(0.f), glm::vec3(-M_PI/4,0,0))
    {}

void Scene::update() {

}

void Scene::render() {
    phongShader.use();
    phongShader.setUniform("view", camera.getViewMatrix());
    phongShader.setUniform("projection", camera.getProjectionMatrix());
    phongShader.setUniform("model", glm::mat4(1.f));
    phongShader.setUniform("viewPos", camera.getViewPosition());
    phongShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 1));
    phongShader.setUniform("material.shininess", 16);
    phongShader.setUniform("pointLight.position", glm::vec3(0,2,1));
    phongShader.setUniform("pointLight.color", glm::vec3(1));
    phongShader.setUniform("pointLight.strength", 4.f);
    phongShader.setUniform("pointLight.constantAttenuation", 1.0f);
    phongShader.setUniform("pointLight.linearAttenuation", 0.7f);
    phongShader.setUniform("pointLight.quadraticAttenuation", 1.8f);

    robot.render(phongShader);
}
