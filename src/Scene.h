//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_SCENE_H
#define PUMAROBOT_SCENE_H


#include "robot/Robot.h"
#include "camera/CameraAnchorFree.h"
#include "app/AppContext.h"

class Scene {

    Shader whiteShader;
    Shader pbrShader;
    Shader shadowShader;
    Shader skyboxShader;
    Shader trailShader;
    Shader pointShader;
    Shader flameShader;
    Shader sparkShader;

    AppContext &appContext;

    void drawMirrorScene(PointLight &pointLight);
    void setupMirrorPhong(PointLight &pointLight);
    void drawSceneNoMirror(bool drawCylinder = true);
    void drawSceneOnlyMirrorFront();

    void drawShadowVolume(PointLight &pointLight);
    void setupPhong(PointLight &pointLight);
    void drawScene();
    void createShadowMask(PointLight &pointLight);
    void setupShadowedPhong(PointLight &pointLight);

    void drawFlames();
    void drawFlamesNormal();
    void drawFlamesMirrored();
    void drawSkybox();
    void drawTrail();
    void drawPointLight(Point &point);
    void drawSkyboxMirrored();
    void drawSparks();

public:
    explicit Scene(AppContext &appContext);
    void update();
    void render();
};


#endif //PUMAROBOT_SCENE_H
