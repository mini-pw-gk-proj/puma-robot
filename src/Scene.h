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

    void drawMirrorScene(PointLight light);
    void setupMirrorPhong(PointLight light);
    void drawSceneNoMirror(bool drawCylinder = true);
    void drawSceneOnlyMirrorFront();
    void drawSceneOnlyMirrorBack();

    void drawShadowVolume();
    void setupPhong(PointLight light);
    void drawScene();
    void createShadowMask();
    void setupShadowedPhong();

public:
    explicit Scene(AppContext &appContext);
    void update();
    void render();


    void drawFlames();

    void drawFlamesNormal();

    void drawFlamesMirrored();

    void drawSkybox();

    void drawTrail();

    void drawPointLight();

    void drawSkyboxMirrored();

    void drawSparks();
};


#endif //PUMAROBOT_SCENE_H
