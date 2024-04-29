//
// Created by faliszewskii on 18.04.24.
//

#include "Scene.h"


Scene::Scene(AppContext &appContext) :
        whiteShader("../res/shaders/basic/position.vert", "../res/shaders/basic/white.frag"),
        phongShader("../res/shaders/phong/phong.vert", "../res/shaders/phong/phong.frag"),
        shadowShader("../res/shaders/shadow/shadow.vert", "../res/shaders/shadow/shadow.geom","../res/shaders/shadow/shadow.frag"),
        skyboxShader("../res/shaders/skybox/skybox.vert","../res/shaders/skybox/skybox.frag"),
        trailShader("../res/shaders/trail/trail.vert","../res/shaders/trail/trail.geom", "../res/shaders/trail/trail.frag"),
        appContext(appContext)
    {}

void Scene::update() {
    auto timeS = float(glfwGetTime());

    appContext.robot->update(timeS);

    appContext.trail->update(appContext.robot->kinematics.movementState != RobotKinematics::AnimatedInverseKinematics);
}

void Scene::render() {
    appContext.frameBufferManager->bind();

    // Render scene as if it was in shadow
    auto t = appContext.pointLight;
    t.strength = 1; // Let a little bit of light in the shadows.
    setupPhong(t);
    drawScene();

    // Render shadowed scene
    createShadowMask();
    setupShadowedPhong();
    drawScene();

    // Clean-up
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glDepthFunc(GL_LESS);

    // Skybox
    skyboxShader.use();
    skyboxShader.setUniform("view", appContext.camera.getNoTranslationViewMatrix());
    skyboxShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    skyboxShader.setUniform("skybox", 0);
    appContext.skybox->render();

    // Trail
    trailShader.use();
    trailShader.setUniform("view", appContext.camera.getViewMatrix());
    trailShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    appContext.trail->render(trailShader);


    appContext.frameBufferManager->unbind();
}

void Scene::setupShadowedPhong() {
    // Render scene with light where stencil is zero
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFunc(GL_EQUAL, 0, 0xFF);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
    glPolygonOffset(0, 0);

    phongShader.use();
    appContext.pointLight.setupPointLight(phongShader);
}

void Scene::createShadowMask() {
    // 1. Turn off depth and color buffers
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    // 2. Use front-face culling
    glCullFace(GL_FRONT);

    // 3. Set the stencil operation to increment on depth fail (only count shadows behind the object).
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);

    // Offset shadow volume a little bit to mitigate z-fighting.
    glPolygonOffset(0.3, 0.3);

    // 4. Render the shadow volumes.
    drawShadowVolume();

    // 5. Use back-face culling.
    glCullFace(GL_BACK);

    // 6. Set the stencil operation to decrement on depth fail.
    glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);

    // 7. Render the shadow volumes.
    drawShadowVolume();
}

void Scene::drawShadowVolume() {
    shadowShader.use();
    shadowShader.setUniform("view", appContext.camera.getViewMatrix());
    shadowShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    shadowShader.setUniform("lightPos", appContext.pointLight.position);

    appContext.mirror->renderShadow(shadowShader);
    appContext.cylinder->renderShadow(shadowShader);
    appContext.robot->renderShadow(shadowShader);
}

void Scene::setupPhong(PointLight light) {
    phongShader.use();
    phongShader.setUniform("view", appContext.camera.getViewMatrix());
    phongShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    phongShader.setUniform("viewPos", appContext.camera.getViewPosition());
    phongShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 1));
    phongShader.setUniform("material.shininess", 16);
    light.setupPointLight(phongShader);
}

void Scene::drawScene() {
    appContext.robot->render(phongShader);
    appContext.room->render(phongShader);
    appContext.cylinder->render(phongShader);
    appContext.mirror->render(phongShader);
}

