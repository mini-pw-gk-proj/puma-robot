//
// Created by Bartek Jadczak on 27/04/2024.
//

#include "Cylinder.h"

Cylinder::Cylinder ()
{
    auto cylinder = generateCylinder(0.5f, 2, 15);
    mesh = std::make_unique<Mesh<PositionNormalVertex>>(cylinder.vertices, cylinder.triagleIndices);
}

void Cylinder::render (Shader &shader)
{
    glm::mat4 model(1.0f);
    model = glm::scale(model, glm::vec3(2,1,1));
    model = glm::rotate(model, (float)M_PI/2, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.0f, 0.0f, -2.0f});
    shader.setUniform("model", model);
    mesh->render();
}

Model Cylinder::generateCylinder (float radius, float height, int slices)
{
    Model cylinderModel;
    std::vector<PositionNormalVertex> vertices;
    std::vector<unsigned int> indices;

    // Generate vertices
    float angleStep = glm::two_pi<float>() / static_cast<float>(slices);
    glm::vec3 topCenter(0.0f, height / 2.0f, 0.0f);
    glm::vec3 bottomCenter(0.0f, -height / 2.0f, 0.0f);

    // Generate side vertices
    for (int i = 0; i <= slices; ++i) {
        float angle = static_cast<float>(i) * angleStep;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        // Top vertex
        vertices.push_back({glm::vec3(x, height / 2.0f, z), glm::normalize(glm::vec3(x, 0.0f, z))});

        // Bottom vertex
        vertices.push_back({glm::vec3(x, -height / 2.0f, z), glm::normalize(glm::vec3(x, 0.0f, z))});
    }

    // Generate indices for the sides
    for (int i = 0; i < slices * 2; i += 2) {
        // Triangle 1
        indices.push_back(i);
        indices.push_back(i + 3);
        indices.push_back(i + 1);

        // Triangle 2
        indices.push_back(i);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }

    // Generate indices for the top and bottom faces
    for (int i = 0; i < slices; ++i) {
        // Top face
        indices.push_back(i * 2);
        indices.push_back(vertices.size() / 2);
        indices.push_back((i + 1) * 2);

        // Bottom face
        indices.push_back(i * 2 + 1);
        indices.push_back((i + 1) * 2 + 1);
        indices.push_back(vertices.size() / 2 + 1);
    }

    // Assign vertices and indices to the model
    cylinderModel.vertices = vertices;
    cylinderModel.triagleIndices = indices;

    return cylinderModel;

}
