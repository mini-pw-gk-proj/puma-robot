//
// Created by faliszewskii on 27.04.24.
//

#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Importer.h"

Model Importer::loadModel(const std::string &path) {
    Model model;

    auto rawModel = loadRawModel(path);

    for(auto &normal : rawModel.normals) {
        model.vertices.push_back({rawModel.uniqueVertices[normal.uniqueVertexId], normal.normal});
    }
    model.triagleIndices.reserve(3 * rawModel.triangles.size());
    for(auto &triangle : rawModel.triangles) {
        model.triagleIndices.push_back(triangle[0]);
        model.triagleIndices.push_back(triangle[1]);
        model.triagleIndices.push_back(triangle[2]);
    }

    model.triagleAdjacencyIndices.reserve(6 * rawModel.triangles.size());
    for(auto &triangle : rawModel.triangles) {
        model.triagleAdjacencyIndices.push_back(triangle[0]);
        model.triagleAdjacencyIndices.push_back(triangle[1]);
        model.triagleAdjacencyIndices.push_back(triangle[2]);
        // TODO TriangleAdjacency
        model.triagleAdjacencyIndices.push_back(0);
        model.triagleAdjacencyIndices.push_back(0);
        model.triagleAdjacencyIndices.push_back(0);
    }

    return model;
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
