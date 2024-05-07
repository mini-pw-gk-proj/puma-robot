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
        flameShader("../res/shaders/flame/flame.vert", "../res/shaders/flame/flame.geom","../res/shaders/flame/flame.frag"),
        sparkShader("../res/shaders/spark/spark.vert", "../res/shaders/spark/spark.geom","../res/shaders/spark/spark.frag"),
        appContext(appContext)
    {}

void Scene::update() {
    auto timeS = float(glfwGetTime());

    appContext.robot->update(timeS);

    appContext.trail->update(appContext.robot->kinematics.movementState != RobotKinematics::AnimatedInverseKinematics);
    appContext.light->updateColor(glm::vec4(appContext.pointLight.color, 1.0f));
    appContext.light->updatePosition(appContext.pointLight.position);

    appContext.sparks->update(appContext.robot->kinematics.movementState == RobotKinematics::AnimatedInverseKinematics);
}

void Scene::render() {
    appContext.frameBufferManager->bind();

    drawSkybox();

    // Mirror world
    setupPhong(appContext.pointLight);
    drawMirrorScene(appContext.pointLight);

    // Render scene
    auto t = appContext.pointLight;
    t.strength = 0.15; // Let a little bit of light in the shadows.
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

    if(appContext.robot->onFire) drawFlamesNormal();

    drawTrail();
    drawPointLight();
    drawSparks();

    appContext.frameBufferManager->unbind();
}

void Scene::drawSparks() {
    sparkShader.use();
    sparkShader.setUniform("view", appContext.camera.getViewMatrix());
    sparkShader.setUniform("projection", appContext.camera.getProjectionMatrix());
    sparkShader.setUniform("viewPos", appContext.camera.getViewPosition());
    appContext.sparks->render(sparkShader);
}

void Scene::drawPointLight() {
    pointShader.use();
    pointShader.setUniform("view", appContext.camera->getViewMatrix());
    pointShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    appContext.light->render(pointShader);
}

void Scene::drawTrail() {
    trailShader.use();
    trailShader.setUniform("view", appContext.camera->getViewMatrix());
    trailShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    appContext.trail->render(trailShader);
}

void Scene::drawSkybox() {
    skyboxShader.use();
    skyboxShader.setUniform("view", appContext.camera->getNoTranslationViewMatrix());
    skyboxShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    skyboxShader.setUniform("skybox", 0);
    appContext.skybox->render();
}

void Scene::drawSkyboxMirrored() {
    skyboxShader.use();
    skyboxShader.setUniform("view", glm::mat4(glm::mat3(appContext.camera->getMirrorViewMatrix())));
    skyboxShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    skyboxShader.setUniform("skybox", 0);
    appContext.skybox->render();
}

void Scene::drawFlames() {
    flameShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    flameShader.setUniform("viewPos", appContext.camera->getViewPosition());
    flameShader.setUniform("time", (float)glfwGetTime());
    flameShader.setUniform("screenX", appContext.camera->screenWidth);
    flameShader.setUniform("noise", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, appContext.flame->noiseTextureId);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    appContext.robot->renderShadow(flameShader);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Scene::drawFlamesNormal() {
    flameShader.use();
    flameShader.setUniform("view", appContext.camera->getViewMatrix());
    drawFlames();
}

void Scene::drawFlamesMirrored() {
    flameShader.use();
    flameShader.setUniform("view", appContext.camera->getMirrorViewMatrix());
    drawFlames();
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
    shadowShader.setUniform("view", appContext.camera->getViewMatrix());
    shadowShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    shadowShader.setUniform("lightPos", appContext.pointLight.position);

    appContext.mirror->renderShadow(shadowShader);
    appContext.cylinder->renderShadow(shadowShader);
    appContext.robot->renderShadow(shadowShader);
}

void Scene::setupPhong(PointLight light) {
    pbrShader.use();
    pbrShader.setUniform("view", appContext.camera->getViewMatrix());
    pbrShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    pbrShader.setUniform("viewPos", appContext.camera->getViewPosition());
    pbrShader.setUniform("isMirror", false);
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

    drawSkyboxMirrored();
    setupMirrorPhong(light);
    drawSceneNoMirror(appContext.camera.getViewPosition().z > -1);
    if(appContext.robot->onFire) drawFlamesMirrored();

    glFrontFace(GL_CCW);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glDepthFunc(GL_LESS);

    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Scene::setupMirrorPhong (PointLight light)
{
    pbrShader.use();
    pbrShader.setUniform("view", appContext.camera->getMirrorViewMatrix());
    pbrShader.setUniform("projection", appContext.camera->getProjectionMatrix());
    pbrShader.setUniform("viewPos", appContext.camera->getViewPosition());
    pbrShader.setUniform("isMirror", false);
    light.setupPointLight(pbrShader);
}

void Scene::drawSceneNoMirror(bool drawCylinder)
{
    appContext.robot->render(pbrShader);
    appContext.room->render(pbrShader);
    if(drawCylinder) appContext.cylinder->render(pbrShader);
}

void Scene::drawSceneOnlyMirrorFront ()
{
    pbrShader.setUniform("isMirror", true);
    appContext.mirror->renderFront(pbrShader);
    pbrShader.setUniform("isMirror", false);
}
void Scene::drawSceneOnlyMirrorBack ()
{
    appContext.mirror->renderBack(pbrShader);
}

