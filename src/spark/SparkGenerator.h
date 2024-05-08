//
// Created by faliszewskii on 07.05.24.
//

#ifndef PUMAROBOT_SPARKGENERATOR_H
#define PUMAROBOT_SPARKGENERATOR_H


#include <vector>
#include <cmath>
#include "Spark.h"
#include "../robot/Robot.h"

class SparkGenerator {
    // TODO: Could be extracted to GUI
    constexpr static int MAX_SPARKS = 200;

    Robot &robot;
    float prevTime{};
public:
    constexpr static float MAX_TTL = 0.5;
    explicit SparkGenerator(Robot &robot) : robot(robot) {}

    std::vector<Spark> sparks;
    void update(bool generate);
};


#endif //PUMAROBOT_SPARKGENERATOR_H
