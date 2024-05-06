//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_IMPORTER_H
#define PUMAROBOT_IMPORTER_H


#include <vector>
#include <string>
#include <array>
#include "glm/vec3.hpp"
#include "Model.h"
#include "RawModel.h"
#include "../mesh/is_vertex.h"
#include "../mesh/PosNorTexVertex.h"

class Importer {
    static RawModel loadRawModel(const std::string &path);
public:
    static Model<PosNorTexVertex> loadModel(const std::string& path);

    static unsigned int findAdj(unsigned int v1, unsigned int v2, std::vector<unsigned int> &adjacentTriangles,
                                RawModel vector);
};


#endif //PUMAROBOT_IMPORTER_H
