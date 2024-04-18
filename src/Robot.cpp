//
// Created by faliszewskii on 18.04.24.
//

#include "Robot.h"

Robot::Robot() {
    meshes.emplace_back(loadMesh("../res/models/mesh1.txt"));
    meshes.emplace_back(loadMesh("../res/models/mesh2.txt"));
    meshes.emplace_back(loadMesh("../res/models/mesh3.txt"));
    meshes.emplace_back(loadMesh("../res/models/mesh4.txt"));
    meshes.emplace_back(loadMesh("../res/models/mesh5.txt"));
    meshes.emplace_back(loadMesh("../res/models/mesh6.txt"));
}

void Robot::update(float timeMs) {

}

void Robot::render(Shader &shader) {
    for (auto &mesh: meshes) {
        mesh.render();
    }
}

Mesh<PositionNormalVertex> Robot::loadMesh(const std::string& path) {
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
    std::vector<glm::vec3> uniqueVertices;
    for(int i=0; i < uniqueVerticesCount; i++) {
        glm::vec3 vertex(std::stof(tokens[caret]), std::stof(tokens[caret+1]), std::stof(tokens[caret+2]));
        caret+=3;
        uniqueVertices.push_back(vertex);
    }

    // Vertices section starts with their count.
    int verticesCount = std::stoi(tokens[caret++]);
    // Load vertices
    std::vector<PositionNormalVertex> vertices;
    for(int i=0; i < verticesCount; i++) {
        int id = std::stoi(tokens[caret++]);
        glm::vec3 normal(std::stof(tokens[caret]), std::stof(tokens[caret+1]), std::stof(tokens[caret+2]));
        caret+=3;
        vertices.push_back({uniqueVertices[id], normal});
    }

    // Triangle section starts with their count.
    int triangleCount = std::stoi(tokens[caret++]);
    // Load indices from triangles
    std::vector<unsigned int> indices;
    indices.reserve(triangleCount*3);
    for(int i=0; i < triangleCount*3; i++) {
        indices.push_back(std::stoi(tokens[caret++]));
    }

    file.close();

    return Mesh(vertices, indices);
}
