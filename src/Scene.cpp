//
// Created by faliszewskii on 18.04.24.
//

#include "Scene.h"


Scene::Scene() : // TODO Remove fixed screen resolution
        plainShader("../res/shaders/basic/position.vert", "../res/shaders/basic/white.frag"),
        camera(1080, 1920, CameraMode::ANCHOR, glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(0.f), glm::vec3(-M_PI/4,0,0))
    {}

void Scene::update() {

}

void Scene::render() {
    plainShader.use();
    plainShader.setUniform("view", camera.getViewMatrix());
    plainShader.setUniform("projection", camera.getProjectionMatrix());
    plainShader.setUniform("model", glm::mat4(1.f));
    robot.render(plainShader);
}
