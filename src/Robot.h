//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_ROBOT_H
#define PUMAROBOT_ROBOT_H


#include "Shader.h"
#include "mesh/Mesh.h"
#include "mesh/PositionNormalVertex.h"
#include "importer/Model.h"

class Robot {

    std::unique_ptr<Mesh<PositionNormalVertex>> standMesh;
    std::vector<Mesh<PositionNormalVertex>> armMeshes;

    std::vector<glm::vec3> armRotationAxisOffsets;
    std::vector<glm::vec3> armRotationAxes;
    glm::vec3 startingNeedlePosition{};
    glm::vec3 startingNeedleOrientation{};

public:
    enum MovementState {
        FreeAngles = 0,
        FreeInverseKinematics = 1,
        AnimatedInverseKinematics = 2,
    };

    std::vector<float> armRotationAngles;
    glm::vec3 needlePosition{};
    glm::vec3 needleOrientation{};
    MovementState movementState;

public:
    Robot(Model& standModel, std::vector<Model>& armModels);

    void update(float timeS);
    void render(Shader &shader);

    static void inverseKinematics(glm::vec3 pos, glm::vec3 normal, float &a1, float &a2, float &a3, float &a4, float &a5);

    void updateNeedle();

    void updateAnimation(float d);
};


#endif //PUMAROBOT_ROBOT_H
