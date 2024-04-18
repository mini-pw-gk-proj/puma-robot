//
// Created by faliszewskii on 18.04.24.
//

#include "Robot.h"

Robot::Robot() {
    std::vector<PositionVertex> vertices{ {{-0.5, -0.5, 0}}, {{0.5, -0.5, 0}}, {{0.5, 0.5, 0}} };
    mesh = std::make_unique<Mesh<PositionVertex>>(vertices);
}

void Robot::update(float timeMs) {

}

void Robot::render(Shader &shader) {
    mesh->render();
}
