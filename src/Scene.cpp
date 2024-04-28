//
// Created by faliszewskii on 18.04.24.
//

#include "Scene.h"


Scene::Scene(AppContext &appContext) :
        whiteShader("../res/shaders/basic/position.vert", "../res/shaders/basic/white.frag"),
        phongShader("../res/shaders/phong/phong.vert", "../res/shaders/phong/phong.frag"),
        appContext(appContext)
    {}

void Scene::update() {
    auto timeS = float(glfwGetTime());

    appContext.robot->update(timeS);
}

void Scene::render() {
    appContext.frameBufferManager->bind();

    phongShader.use();
    phongShader.setUniform("view", appContext.camera.getViewMatrix());
    phongShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    phongShader.setUniform("viewPos", appContext.camera.getViewPosition());
    phongShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 1));
    phongShader.setUniform("material.shininess", 16);
    appContext.pointLight.setupPointLight(phongShader);


    appContext.robot->render(phongShader);
    appContext.room->render(phongShader);
    appContext.cylinder->render(phongShader);

    appContext.frameBufferManager->unbind();
}

