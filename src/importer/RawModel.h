//
// Created by faliszewskii on 27.04.24.
//

#ifndef PUMAROBOT_RAWMODEL_H
#define PUMAROBOT_RAWMODEL_H

#include <vector>
#include <array>
#include "glm/vec3.hpp"

struct RawModel {
    std::vector<glm::vec3> uniqueVertices; // Positions of uniqueVertices.

    struct Normal {
        unsigned int uniqueVertexId;
        glm::vec3 normal;
    };
    std::vector<Normal> normals; // one or more normal vectors can belong to a single uniqueVertex.

    std::vector<std::array<unsigned int, 3>> triangles; // Indices of vertices (not uniqueVertices!) that create a triangle.

    struct Edge {
        std::array<unsigned int, 2> uniqueVerticesIds; // Indices of uniqueVertices connected by the edge.
        std::array<unsigned int, 2> triangleIds; // Indices of triangles these points belong to.
    };
    std::vector<Edge> edges;
};

#endif //PUMAROBOT_RAWMODEL_H
