//
// Created by faliszewskii on 18.04.24.
//

#include "Scene.h"


Scene::Scene(AppContext &appContext) :
        whiteShader("../res/shaders/basic/position.vert", "../res/shaders/basic/white.frag"),
        pbrShader("../res/shaders/pbr/pbr.vert", "../res/shaders/pbr/pbr.frag"),
        shadowShader("../res/shaders/shadow/shadow.vert", "../res/shaders/shadow/shadow.geom","../res/shaders/shadow/shadow.frag"),
        skyboxShader("../res/shaders/skybox/skybox.vert","../res/shaders/skybox/skybox.frag"),
        trailShader("../res/shaders/trail/trail.vert","../res/shaders/trail/trail.geom", "../res/shaders/trail/trail.frag"),
        pointShader("../res/shaders/point/point.vert","../res/shaders/point/point.frag"),
        appContext(appContext)
    {}

void Scene::update() {
    auto timeS = float(glfwGetTime());

    appContext.robot->update(timeS);
    appContext.trail->update(appContext.robot->kinematics.movementState != RobotKinematics::AnimatedInverseKinematics);
    appContext.light->updateColor(glm::vec4(appContext.pointLight.color, 1.0f));
    appContext.light->updatePosition(appContext.pointLight.position);
}

void Scene::render() {
    appContext.frameBufferManager->bind();

    // Mirror world
    drawMirrorScene(appContext.pointLight);

    // Render scene
    auto t = appContext.pointLight;
    t.strength = 0.25; // Let a little bit of light in the shadows.
    setupPhong(t);
    drawSceneOnlyMirrorFront();
    drawSceneOnlyMirrorBack();
    drawSceneNoMirror();

    // Render shadowed scene
    createShadowMask();
    setupShadowedPhong();
    drawSceneNoMirror();

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

    // Point
    pointShader.use();
    pointShader.setUniform("view", appContext.camera.getViewMatrix());
    pointShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    appContext.light->render(pointShader);

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

    pbrShader.use();
    appContext.pointLight.setupPointLight(pbrShader);
}

void Scene::createShadowMask() {
    // 1. Turn off depth and color buffers
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    // 2. Use front-face culling
    glCullFace(GL_FRONT);

    // 3. Set the stencil operation to increment on depth fail (only count shadows behind the object).
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);

    // Offset shadow volume a little bit to mitigate z-fighting.
    glPolygonOffset(0.25, 0.25);

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
    pbrShader.use();
    pbrShader.setUniform("view", appContext.camera.getViewMatrix());
    pbrShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    pbrShader.setUniform("viewPos", appContext.camera.getViewPosition());
    pbrShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 1));
    pbrShader.setUniform("material.shininess", 16);
    light.setupPointLight(pbrShader);
}

void Scene::drawScene() {
    appContext.robot->render(pbrShader);
    appContext.room->render(pbrShader);
    appContext.cylinder->render(pbrShader);
    appContext.mirror->render(pbrShader);
}

void Scene::drawMirrorScene (PointLight light)
{
    // 1. Turn off depth and color buffers
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    // 3. Set the stencil operation to increment on depth fail (only count shadows behind the object).
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    drawSceneOnlyMirrorFront();

    // 6. Set the stencil operation to decrement on depth fail.
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFuncSeparate(GL_FRONT, GL_EQUAL, 1, 0xFF);
    glStencilFuncSeparate(GL_BACK, GL_NEVER, 1, 0xFF);

    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glFrontFace(GL_CW);

    setupMirrorPhong(light);
    drawSceneNoMirror();

    glFrontFace(GL_CCW);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glDepthFunc(GL_LESS);

    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Scene::setupMirrorPhong (PointLight light)
{
    phongShader.use();
    phongShader.setUniform("view", appContext.camera.getMirrorViewMatrix());
    phongShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    phongShader.setUniform("viewPos", appContext.camera.getViewPosition());
    phongShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 1));
    phongShader.setUniform("material.shininess", 16);
    light.setupPointLight(phongShader);
}

void Scene::drawSceneNoMirror ()
{
    appContext.robot->render(phongShader);
    appContext.room->render(phongShader);
    appContext.cylinder->render(phongShader);
}

void Scene::drawSceneOnlyMirrorFront ()
{
    phongShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 0.5));
    appContext.mirror->renderFront(phongShader);
    phongShader.setUniform("material.albedo", glm::vec4(0.8, 0.8, 0.8, 1));
}
void Scene::drawSceneOnlyMirrorBack ()
{
    appContext.mirror->renderBack(phongShader);
}

