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

class Importer {
    static RawModel loadRawModel(const std::string &path);
public:
    static Model loadModel(const std::string& path);
};


#endif //PUMAROBOT_IMPORTER_H
