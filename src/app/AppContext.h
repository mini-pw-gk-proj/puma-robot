//
// Created by faliszewskii on 19.04.24.
//

#ifndef PUMAROBOT_APPCONTEXT_H
#define PUMAROBOT_APPCONTEXT_H


#include "../Robot.h"
#include "../camera/Camera.h"
#include "../framebufferManager/FrameBufferManager.h"

struct AppContext {
    Robot robot;

    Camera camera;

    std::unique_ptr<FrameBufferManager> frameBufferManager;

    bool guiFocus = true;

    void glfw_window_resize(unsigned int width, unsigned int height)
    {
        camera.resize(width, height); // NOLINT(*-narrowing-conversions)
        frameBufferManager->create_buffers(camera.screenWidth, camera.screenHeight);
    }

    AppContext() : // TODO Remove fixed screen resolution
        camera(1920, 1080, CameraMode::ANCHOR, glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(0.f), glm::vec3(-M_PI/4,0,0)),
        frameBufferManager()
        {
            frameBufferManager = std::make_unique<FrameBufferManager>();
            frameBufferManager->create_buffers(camera.screenWidth, camera.screenHeight);
        }
};


#endif //PUMAROBOT_APPCONTEXT_H
