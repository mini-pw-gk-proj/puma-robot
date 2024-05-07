//
// Created by faliszewskii on 28.04.24.
//

#include "Trail.h"

Trail::Trail(Robot &robot) : robot(robot) {
    mesh = std::make_unique<Mesh<EmptyVertex>>(Mesh<EmptyVertex>({EmptyVertex()}, {}, GL_POINTS));
}

void Trail::reset() {
    caret = 0;
    pointCount = 0;
}

void Trail::update(bool shouldReset) {
    if(shouldReset) {
        reset();
        return;
    }
    if(--skip > 0 ) return;
    skip = SKIP;


    if(pointCount < TRAIL_POINTS) pointCount++;

    trailPoints[caret] = robot.kinematics.needlePosition;

    caret++;
    if(caret == TRAIL_POINTS) caret = 0;
}

void Trail::render(Shader &shader) {
    shader.setUniform("trailPoints", trailPoints.data(), trailPoints.size());
    shader.setUniform("pointCount", pointCount);
    shader.setUniform("caret", caret);
    shader.setUniform("startingOpacity", 1.0f);

    mesh->render();
}
