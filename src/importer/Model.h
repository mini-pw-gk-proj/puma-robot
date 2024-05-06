//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_MODEL_H
#define PUMAROBOT_MODEL_H

#include <vector>
#include "../mesh/PositionNormalVertex.h"
#include "../mesh/is_vertex.h"

template<typename TVertex> requires is_vertex<TVertex>
struct Model {
    std::vector<TVertex> vertices;
    std::vector<unsigned int> triagleIndices;
    std::vector<unsigned int> triagleAdjacencyIndices;
};

#endif //PUMAROBOT_MODEL_H
