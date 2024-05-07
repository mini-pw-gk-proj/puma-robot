//
// Created by faliszewskii on 19.04.24.
//

#ifndef PUMAROBOT_APPCONTEXT_H
#define PUMAROBOT_APPCONTEXT_H


#include "../robot/Robot.h"
#include "../room/Room.h"
#include "../cylinder/Cylinder.h"
#include "../mirror/Mirror.h"
#include "../camera/Camera.h"
#include "../framebufferManager/FrameBufferManager.h"
#include "../importer/Importer.h"
#include "../light/PointLight.h"
#include "../skybox/Skybox.h"
#include "../trail/Trail.h"
#include "../point/Point.h"
#include "../flame/Flame.h"
#include "../spark/SparksEntity.h"


struct AppContext {
    std::unique_ptr<Robot> robot;
    std::unique_ptr<Room> room;
    std::unique_ptr<Mirror> mirror;
    std::unique_ptr<Cylinder> cylinder;
    std::unique_ptr<Skybox> skybox;
    std::unique_ptr<Trail> trail;
    std::unique_ptr<Point> light;
    std::unique_ptr<Flame> flame;
    std::unique_ptr<SparksEntity> sparks;

    PointLight pointLight;
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

            auto standModel = Importer::loadModel("../res/models/mesh1.txt");
            std::vector<Model<PosNorTexVertex>> armModels;
            armModels.reserve(5);
            for(int i = 0; i < 5; i++)
                armModels.push_back(Importer::loadModel("../res/models/mesh" + std::to_string(i+2) + ".txt"));
            robot = std::make_unique<Robot>(standModel, armModels);
            room = std::make_unique<Room>();
            cylinder = std::make_unique<Cylinder>();
            mirror = std::make_unique<Mirror>();
            skybox = std::make_unique<Skybox>();
            trail = std::make_unique<Trail>(*robot);
            light = std::make_unique<Point>();
            flame = std::make_unique<Flame>();
            sparks = std::make_unique<SparksEntity>(*robot);
        }
};


#endif //PUMAROBOT_APPCONTEXT_H
