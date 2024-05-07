//
// Created by faliszewskii on 07.05.24.
//

#include "SparkGenerator.h"

void SparkGenerator::update() {
    // WIP
    if(sparks.empty()) sparks.push_back(Spark{
        {},
        robot.kinematics.needlePosition,
        -robot.kinematics.needleOrientation,
        5});
    sparks[0].ttl -= glfwGetTime();
    if(sparks[0].ttl < 0) sparks.pop_back();
    sparks[0].velocity += glm::vec3(0, -9.81, 0);
    sparks[0].prevPos = sparks[0].currPos;
    sparks[0].currPos += sparks[0].velocity;

    // TODO: Implement
    // Kill aged sparks.
    // Check how many can be created.
    // Randomize amount to create.
    // Get normal of the surface to get default velocity vector.
    // Randomize velocities' deviation (speed + angle).
    // Randomize time to live.
    // Create next positions for every spark (for newly created as well as they need at least two point to be drawn)
}
