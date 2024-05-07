//
// Created by faliszewskii on 07.05.24.
//

#ifndef PUMAROBOT_SPARKGENERATOR_H
#define PUMAROBOT_SPARKGENERATOR_H


#include <vector>
#include <cmath>
#include "Spark.h"

class SparkGenerator {
    // TODO: Could be extracted to GUI
    constexpr static int MAX_SPARKS = 100;
    constexpr static float MAX_TTL = 2;
    constexpr static float MAX_ANGLE = M_PI/2;
    constexpr static float MAX_VELOCITY = 2;
public:
    std::vector<Spark> sparks;
    void update();
};


#endif //PUMAROBOT_SPARKGENERATOR_H
