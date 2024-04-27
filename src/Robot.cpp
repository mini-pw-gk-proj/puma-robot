//
// Created by faliszewskii on 18.04.24.
//

#include "Robot.h"

Robot::Robot(Model& standModel, std::vector<Model>& armModels) {
    standMesh = std::make_unique<Mesh<PositionNormalVertex>>(standModel.vertices, standModel.triagleIndices);
    armModels.reserve(armModels.size());
    for(auto &armModel : armModels) {
        armMeshes.emplace_back(armModel.vertices, armModel.triagleIndices);
    }

    armRotationAxes = {
            {0, 1, 0},  // Y-aligned
            {0, 0, 1},  // Z-aligned
            {0, 0, 1},  // Z-aligned
            {1, 0, 0},  // X-aligned
            {0, 0, 1},  // Z-aligned
    };
    armRotationAxisOffsets = {
            {0, 0, 0},          // Y-aligned
            {0, 0.27f, 0},      // Z-aligned
            {-0.91f, 0.27f, 0}, // Z-aligned
            {0, 0.27f, -0.26},  // X-aligned
            {-1.72f, 0.27f, 0}, // Z-aligned
    };
    startingNeedlePosition = {-2.05f, 0.27f, 0};
    startingNeedleOrientation = {1.f, 0, 0};

    armRotationAngles = std::vector<float>(5);
    needlePosition = startingNeedlePosition;
    needleOrientation = startingNeedleOrientation;
    movementState = FreeAngles;
}

void Robot::update(float timeS) {
    switch(movementState) {
        case FreeAngles:
            updateNeedle();
            break;
        case FreeInverseKinematics:
            inverseKinematics(needlePosition, needleOrientation, armRotationAngles[0], armRotationAngles[1], armRotationAngles[2], armRotationAngles[3], armRotationAngles[4]);
            break;
        case AnimatedInverseKinematics:
            updateAnimation(timeS);
            inverseKinematics(needlePosition, needleOrientation, armRotationAngles[0], armRotationAngles[1], armRotationAngles[2], armRotationAngles[3], armRotationAngles[4]);
            break;
    }
}

void Robot::updateNeedle() {
    glm::mat4 model(1.0f);
    for (int i = 0; i < armRotationAngles.size(); i++) {
        glm::mat4 localModel(1.0f);
        model = glm::translate(model, armRotationAxisOffsets[i]);
        model = glm::rotate(model, armRotationAngles[i], armRotationAxes[i]);
        model = glm::translate(model, -armRotationAxisOffsets[i]);
        model *= localModel;
    }
    needlePosition = model * glm::vec4(startingNeedlePosition, 1);
    needleOrientation = model * glm::vec4(startingNeedleOrientation, 0);
}

void Robot::inverseKinematics(glm::vec3 pos, glm::vec3 normal, float &a1, float &a2, float &a3, float &a4, float &a5) {
    float l1 = .91f, l2 = .81f, l3 = .33f, dy = .27f, dz = .26f;
    normal = glm::normalize(normal);
    glm::vec3 pos1 = pos + normal * l3;
    float e = sqrtf(pos1.z*pos1.z+pos1.x*pos1.x-dz*dz);
    a1 = atan2(pos1.z, -pos1.x)+atan2(dz, e);
    glm::vec3 pos2(e, pos1.y-dy, .0f);
    a3 = -acosf(std::min(1.0f,(pos2.x*pos2.x+pos2.y*pos2.y-l1*l1-l2*l2) / (2.0f*l1*l2)));
    float k = l1 + l2 * cosf(a3), l = l2 * sinf(a3);
    a2 = -atan2(pos2.y,sqrtf(pos2.x*pos2.x+pos2.z*pos2.z))-atan2(l,k);
    glm::vec3 normal1;
    normal1 = glm::vec3(glm::rotate(glm::mat4(1.f), -a1, glm::vec3(0,1,0)) * glm::vec4(normal, .0f));
    normal1 = glm::vec3(glm::rotate(glm::mat4(1.f), -(a2+a3), glm::vec3(0,0,1)) * glm::vec4(normal1, .0f));
    a5 = acosf(normal1.x);
    a4 = atan2(normal1.z, normal1.y);
}

void Robot::updateAnimation(float timeS) {
    float speed = 4;
    float r = 0.5;
    float distance = 1.7;
    float angle = M_PI/6;

    glm::vec4 circle(0.f, r*cos(timeS * speed), r * sin(timeS*speed), 1.f);
    circle = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0 ,1)) * circle;
    circle += glm::vec4(-distance,0,0,0);
    needlePosition = circle;

    glm::vec4 orientation = glm::vec4(1, 0, 0, 0);
    orientation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0 ,1)) * orientation;
    needleOrientation = orientation;
}

void Robot::render(Shader &shader) {

    shader.setUniform("model", glm::mat4(1.0f));
    standMesh->render();

    glm::mat4 model(1.0f);
    for (int i = 0; i < armMeshes.size(); i++) {
        auto &mesh = armMeshes[i];
        glm::mat4 localModel(1.0f);
        model = glm::translate(model, armRotationAxisOffsets[i]);
        model = glm::rotate(model, armRotationAngles[i], armRotationAxes[i]);
        model = glm::translate(model, -armRotationAxisOffsets[i]);
        model *= localModel;
        shader.setUniform("model", model);
        mesh.render();
    }
}
