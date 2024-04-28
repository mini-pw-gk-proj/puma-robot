//
// Created by Bartek Jadczak on 28/04/2024.
//

#include "Mirror.h"

Model Mirror::generateMirrorPlane ()
{
    Model mirrorModel;

    std::vector<PositionNormalVertex> vertices = {
            // Front face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},

            // Back face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},

    };

    std::vector<unsigned int> triangleIndices = {
            // Front face
            0, 1, 2,
            0, 2, 3,

            // Back face
            4, 6, 5,
            4, 7, 6,
    };

    std::vector<unsigned int> triangleAdjacencyIndices = {
            // Front face
            0, 1, 2,  2, 0, 3,
            0, 2, 3,  1, 0, 2,

            // Back face
            4, 6, 5,  7, 4, 6,
            4, 7, 6,  6, 4, 5,
    };

    // Assign vertices and indices to the model
    mirrorModel.vertices = vertices;
    mirrorModel.triagleIndices = triangleIndices;
    mirrorModel.triagleAdjacencyIndices = triangleAdjacencyIndices;

    return mirrorModel;
}

Mirror::Mirror ()
{
    auto mirror = generateMirrorPlane();
    mesh = std::make_unique<Mesh<PositionNormalVertex>>(mirror.vertices, mirror.triagleIndices);
    meshVolume = std::make_unique<Mesh<PositionNormalVertex>>(mirror.vertices, mirror.triagleAdjacencyIndices, GL_TRIANGLES_ADJACENCY);
}

void Mirror::render (Shader &shader)
{
    shader.setUniform("model", getModel());
    mesh->render();
}

void Mirror::renderShadow(Shader &shader) {
    shader.setUniform("model", getModel());
    meshVolume->render();
}

glm::mat4 Mirror::getModel() {
    glm::mat4 model(1.0f);
    model = glm::rotate(model, (float)M_PI/6, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.49f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(2,2,2));
    return model;
}
