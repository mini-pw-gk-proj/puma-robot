//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_ROBOTKINEMATICS_H
#define PUMAROBOT_ROBOTKINEMATICS_H


#include <vector>
#include <array>
#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "../fourier/FourierShape.h"
#include "../fourier/FourierShapeFactory.h"

class RobotKinematics {
    static constexpr int MODEL_COUNT = 6;
    static constexpr int ARM_COUNT = 5;

    FourierShape piShape = FourierShapeFactory::createPi();

    std::array<glm::vec3, ARM_COUNT> armRotationAxisOffsets{};
    std::array<glm::vec3, ARM_COUNT> armRotationAxes{};
    glm::vec3 startingNeedlePosition{};
    glm::vec3 startingNeedleOrientation{};

    std::array<glm::mat4, MODEL_COUNT> modelMatrices{};

public:
    enum MovementState {
        FreeAngles = 0,
        FreeInverseKinematics = 1,
        AnimatedInverseKinematics = 2,
    };
    enum Animation {
        Pi = 0,
        Infinity = 1,
        Chaotic = 2,
        Circle = 3,
    };

    std::array<float, ARM_COUNT> armRotationAngles{};
    glm::vec3 needlePosition{};
    glm::vec3 needleOrientation{};
    MovementState movementState;
    Animation animation = Pi;

private:
    static void inverseKinematics(glm::vec3 pos, glm::vec3 normal, float &a1, float &a2, float &a3, float &a4, float &a5);

    void updateNeedle();

    void updateAnimation(float d);

public:
    RobotKinematics();

    glm::mat4 getModel(int i);

    void update(float timeS);
};


#endif //PUMAROBOT_ROBOTKINEMATICS_H
