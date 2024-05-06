//
// Created by Bartek Jadczak on 27/04/2024.
//

#include <random>
#include "Cylinder.h"

Cylinder::Cylinder () :
        columnTexture("../res/textures/column.png")
{
    auto cylinder = generateCylinder(0.5f, 2, 15);
    mesh = std::make_unique<Mesh<PosNorTexVertex>>(cylinder.vertices, cylinder.triagleIndices);
    meshVolume = std::make_unique<Mesh<PosNorTexVertex>>(cylinder.vertices, cylinder.triagleAdjacencyIndices, GL_TRIANGLES_ADJACENCY);


}

void Cylinder::render (Shader &shader) {
    shader.setUniform("material.hasTexture", true);
    shader.setUniform("texture", 0);
    columnTexture.bind(0);
    shader.setUniform("model", getModel());
    material.setupMaterial(shader);
    mesh->render();
}

void Cylinder::renderShadow(Shader &shader) {
    shader.setUniform("model", getModel());
    meshVolume->render();
}

glm::mat4 Cylinder::getModel() {
    glm::mat4 model(1.0f);
    model = glm::rotate(model, (float)M_PI/2, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.0f, 0.0f, -2.0f});
    model = glm::scale(model, glm::vec3(1,2,1));
    model = glm::rotate(model, (float)M_PI, glm::vec3(0,1,0));
    return model;
}

Model<PosNorTexVertex> Cylinder::generateCylinder (float radius, float height, int slices) {
    Model<PosNorTexVertex> cylinderModel;
    std::vector<PosNorTexVertex> vertices;
    std::vector<unsigned int> indices;

    // Generate vertices
    float textureStep = 1.f / static_cast<float>(slices);
    float angleStep = glm::two_pi<float>() / static_cast<float>(slices);
    glm::vec3 topCenter(0.0f, height / 2.0f, 0.0f);
    glm::vec3 bottomCenter(0.0f, -height / 2.0f, 0.0f);

    // Sizes
    int partSize = slices*2;

    // Indices
    int startFaces = slices*2;
    int topMiddle = slices*4;
    int bottomMiddle = slices*4 + 1;

    // Generate side vertices
    for (int i = 0; i < slices; ++i) {
        float angle = static_cast<float>(i) * angleStep;
        float texCoord = static_cast<float>(i) * textureStep;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        // Top vertex
        vertices.push_back({glm::vec3(x, height / 2.0f, z), glm::normalize(glm::vec3(x, 0.0f, z)), glm::vec2(texCoord, 0)});

        // Bottom vertex
        vertices.push_back({glm::vec3(x, -height / 2.0f, z), glm::normalize(glm::vec3(x, 0.0f, z)), glm::vec2(texCoord, 1)});
    }

    // Generate side vertices for faces
    for (int i = 0; i < slices; ++i) {
        float angle = static_cast<float>(i) * angleStep;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        // Top vertex for faces
        vertices.push_back({glm::vec3(x, height / 2.0f, z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2()});

        // Bottom vertex for faces
        vertices.push_back({glm::vec3(x, -height / 2.0f, z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2()});
    }

    // Add middle points
    // Top vertex for faces
    vertices.push_back({glm::vec3(0, height / 2.0f, 0), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2()});

    // Bottom vertex for faces
    vertices.push_back({glm::vec3(0, -height / 2.0f, 0), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2()});


    // Generate indices for the sides
    for (int i = 0; i < slices * 2; i += 2) {
        int nextTop = i + 2 >= partSize ? 0 : i + 2;
        int nextBottom = i + 3 >= partSize ? 1 : i + 3;
        // Triangle 1
        indices.push_back(i);
        indices.push_back(nextBottom);
        indices.push_back(i + 1);

        // Triangle 2
        indices.push_back(i);
        indices.push_back(nextTop);
        indices.push_back(nextBottom);
    }

    // Generate indices for the top and bottom faces
    for (int i = 0; i <= slices; ++i) {
        int nextTop =  (i + 1) * 2 >= partSize ? 0 : (i + 1) * 2;
        int nextBottom = (i + 1) * 2 + 1 >= partSize ? 1 : (i + 1) * 2 + 1;
        // Top face
        indices.push_back(startFaces + i * 2);
        indices.push_back(topMiddle);
        indices.push_back(startFaces + nextTop);

        // Bottom face
        indices.push_back(startFaces + i * 2 + 1);
        indices.push_back(startFaces + nextBottom);
        indices.push_back(bottomMiddle);
    }

    // Triangle adjacency
    std::vector<unsigned int> adjacencyIndices;

    // Generate indices for the sides
    for (int i = 0; i < slices * 2; i += 2) {
        int prevTop = i - 2 < 0 ? partSize - 2 : i - 2;
        int prevBottom = i - 1 < 0 ? partSize - 1 : i - 1;
        int bottom = i + 1;
        int top = i;
        int nextTop = i + 2 >= partSize ? 0 : i + 2;
        int nextBottom = i + 3 >= partSize ? 1 : i + 3;
        int nextNextBottom = nextBottom + 2 >= partSize ? 1 : nextBottom + 2;

        // Triangle 1
        adjacencyIndices.push_back(top);
        adjacencyIndices.push_back(nextBottom);
        adjacencyIndices.push_back(bottom);
        adjacencyIndices.push_back(nextTop);
        adjacencyIndices.push_back(bottomMiddle);
        adjacencyIndices.push_back(prevTop);

        // Triangle 2
        adjacencyIndices.push_back(top);
        adjacencyIndices.push_back(nextTop);
        adjacencyIndices.push_back(nextBottom);
        adjacencyIndices.push_back(topMiddle);
        adjacencyIndices.push_back(nextNextBottom);
        adjacencyIndices.push_back(bottom);
    }

    // Generate indices for the faces
    for (int i = 0; i < slices * 2; i += 2) {
        int prevTop = i - 2 < 0 ? partSize - 2 : i - 2;
        int prevBottom = i - 1 < 0 ? partSize - 1 : i - 1;
        int bottom = i + 1;
        int top = i;
        int nextTop = i + 2 >= partSize ? 0 : i + 2;
        int nextNextTop = nextTop + 2 >= partSize ? 0 : nextTop + 2;
        int nextBottom = i + 3 >= partSize ? 1 : i + 3;
        int nextNextBottom = nextBottom + 2 >= partSize ? 1 : nextBottom + 2;

        // Top face
        adjacencyIndices.push_back(top);
        adjacencyIndices.push_back(topMiddle);
        adjacencyIndices.push_back(nextTop);
        adjacencyIndices.push_back(prevTop);
        adjacencyIndices.push_back(nextNextTop);
        adjacencyIndices.push_back(bottom);

        // Bottom face
        adjacencyIndices.push_back(bottom);
        adjacencyIndices.push_back(nextBottom);
        adjacencyIndices.push_back(bottomMiddle);
        adjacencyIndices.push_back(nextTop);
        adjacencyIndices.push_back(nextNextBottom);
        adjacencyIndices.push_back(prevBottom);
    }

    // Assign vertices and indices to the model
    cylinderModel.vertices = vertices;
    cylinderModel.triagleIndices = indices;
    cylinderModel.triagleAdjacencyIndices = adjacencyIndices;

    return cylinderModel;

}
