//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_MODEL_H
#define PUMAROBOT_MODEL_H

#include <vector>
#include "../mesh/PositionNormalVertex.h"

struct Model {
    std::vector<PositionNormalVertex> vertices;
    std::vector<unsigned int> triagleIndices;
    std::vector<unsigned int> triagleAdjacencyIndices;
};

#endif //PUMAROBOT_MODEL_H
