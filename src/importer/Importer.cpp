//
// Created by faliszewskii on 27.04.24.
//

#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Importer.h"

Model<PosNorTexVertex> Importer::loadModel(const std::string &path) {
    Model<PosNorTexVertex> model;

    auto rawModel = loadRawModel(path);

    for(auto &normal : rawModel.normals) {
        model.vertices.push_back({rawModel.uniqueVertices[normal.uniqueVertexId], normal.normal, glm::vec2()});
    }
    model.triagleIndices.reserve(3 * rawModel.triangles.size());
    for(auto &triangle : rawModel.triangles) {
        model.triagleIndices.push_back(triangle[0]);
        model.triagleIndices.push_back(triangle[1]);
        model.triagleIndices.push_back(triangle[2]);
    }

    model.triagleAdjacencyIndices.reserve(6 * rawModel.triangles.size());
    for(int i = 0; i < rawModel.triangles.size(); i++) {
        auto &triangle = rawModel.triangles[i];
        model.triagleAdjacencyIndices.push_back(triangle[0]);
        model.triagleAdjacencyIndices.push_back(triangle[1]);
        model.triagleAdjacencyIndices.push_back(triangle[2]);

        std::vector<unsigned int> adjecentTriangles;
        for(auto &edge : rawModel.edges) {
            if(i == edge.triangleIds[0]) adjecentTriangles.push_back(edge.triangleIds[1]);
            if(i == edge.triangleIds[1]) adjecentTriangles.push_back(edge.triangleIds[0]);
        }
        assert(adjecentTriangles.size() == 3);

        model.triagleAdjacencyIndices.push_back(findAdj(triangle[0], triangle[1], adjecentTriangles, rawModel));
        model.triagleAdjacencyIndices.push_back(findAdj(triangle[1], triangle[2], adjecentTriangles, rawModel));
        model.triagleAdjacencyIndices.push_back(findAdj(triangle[0], triangle[2], adjecentTriangles, rawModel));
    }

    return model;
}

unsigned int Importer::findAdj(unsigned int v1, unsigned int v2, std::vector<unsigned int> &adjacentTriangles, RawModel rawModel) {
    v1 = rawModel.normals[v1].uniqueVertexId;
    v2 = rawModel.normals[v2].uniqueVertexId;
    for(auto &triangleId : adjacentTriangles) {
        auto triangle = rawModel.triangles[triangleId];
        triangle[0] = rawModel.normals[triangle[0]].uniqueVertexId;
        triangle[1] = rawModel.normals[triangle[1]].uniqueVertexId;
        triangle[2] = rawModel.normals[triangle[2]].uniqueVertexId;
        if((v1 == triangle[0] && v2 == triangle[1]) || (v2 == triangle[0] && v1 == triangle[1]))
            return triangle[2];
        if((v1 == triangle[1] && v2 == triangle[2]) || (v2 == triangle[1] && v1 == triangle[2]))
            return triangle[0];
        if((v1 == triangle[0] && v2 == triangle[2]) || (v2 == triangle[0] && v1 == triangle[2]))
            return triangle[1];
    }
    assert(false);
}

RawModel Importer::loadRawModel(const std::string &path) {
    RawModel model;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw(std::runtime_error("Error opening file."));
    }

    std::vector<std::string> tokens;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
    }

    int caret = 0;

    // Unique vertices section starts with their count.
    int uniqueVerticesCount = std::stoi(tokens[caret++]);
    // Load unique vertices
    model.uniqueVertices.reserve(uniqueVerticesCount);
    for(int i=0; i < uniqueVerticesCount; i++) {
        glm::vec3 vertex(std::stof(tokens[caret+0]), std::stof(tokens[caret+1]), std::stof(tokens[caret+2]));
        caret+=3;
        model.uniqueVertices.push_back(vertex);
    }

    // Vertices section starts with their count.
    int verticesCount = std::stoi(tokens[caret++]);
    // Load vertices with unique normals
    model.normals.reserve(verticesCount);
    for(int i=0; i < verticesCount; i++) {
        unsigned int id = std::stoi(tokens[caret++]);
        glm::vec3 normal(std::stof(tokens[caret]), std::stof(tokens[caret+1]), std::stof(tokens[caret+2]));
        caret+=3;
        model.normals.push_back({id, normal});
    }

    // Triangle section starts with their count.
    int triangleCount = std::stoi(tokens[caret++]);
    // Load indices from triangles
    model.triangles.reserve(triangleCount);
    for(int i=0; i < triangleCount; i++) {
        model.triangles.push_back({
            static_cast<unsigned int>(std::stoi(tokens[caret+0])),
            static_cast<unsigned int>(std::stoi(tokens[caret+1])),
            static_cast<unsigned int>(std::stoi(tokens[caret+2])),
            });
        caret+=3;
    }

    // Edge section starts with their count.
    int edgeCount = std::stoi(tokens[caret++]);
    // Load edge vertices and triangles
    model.edges.reserve(edgeCount);
    for(int i=0; i < edgeCount; i++) {
        model.edges.push_back({{
            static_cast<unsigned int>(std::stoi(tokens[caret+0])),
            static_cast<unsigned int>(std::stoi(tokens[caret+1])),
            }, {
            static_cast<unsigned int>(std::stoi(tokens[caret+2])),
            static_cast<unsigned int>(std::stoi(tokens[caret+3])),
            }
        });
        caret+=4;
    }

    file.close();
    return model;
}
