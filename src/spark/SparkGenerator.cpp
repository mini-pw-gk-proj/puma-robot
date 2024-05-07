//
// Created by faliszewskii on 07.05.24.
//

#include "SparkGenerator.h"

void SparkGenerator::update() {
    // WIP
    if(sparks.size() < MAX_SPARKS)
        sparks.push_back(Spark{
                {},
                robot.kinematics.needlePosition,
                robot.kinematics.needleOrientation*0.1f,
                0.1});
    for(auto &spark : sparks) {
        spark.ttl -= glfwGetTime() - prevTime;
        prevTime = glfwGetTime();
        spark.prevPos = spark.currPos;
        spark.currPos += spark.velocity;
        spark.velocity += glm::vec3(0, -9.81, 0)*0.001f;
    }
    sparks.erase(std::remove_if(sparks.begin(), sparks.end(), [&](const auto &item) {
        return item.ttl < 0;
    }), sparks.end());

    // TODO: Implement
    // Kill aged sparks.
    // Check how many can be created.
    // Randomize amount to create.
    // Get normal of the surface to get default velocity vector.
    // Randomize velocities' deviation (speed + angle).
    // Randomize time to live.
    // Create next positions for every spark (for newly created as well as they need at least two point to be drawn)
}
