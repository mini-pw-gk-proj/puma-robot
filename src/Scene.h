//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_SCENE_H
#define PUMAROBOT_SCENE_H


#include "robot/Robot.h"
#include "camera/Camera.h"
#include "app/AppContext.h"

class Scene {

    Shader whiteShader;
    Shader phongShader;
    Shader shadowShader;

    AppContext &appContext;

    void drawMirrorScene(PointLight light);
    void setupMirrorPhong(PointLight light);
    void drawSceneNoMirror();
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


};


#endif //PUMAROBOT_SCENE_H
