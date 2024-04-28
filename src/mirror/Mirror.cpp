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

    // Assign vertices and indices to the model
    mirrorModel.vertices = vertices;
    mirrorModel.triagleIndices = triangleIndices;

    return mirrorModel;
}

Mirror::Mirror ()
{
    auto room = generateMirrorPlane();
    mesh = std::make_unique<Mesh<PositionNormalVertex>>(room.vertices, room.triagleIndices);
}

void Mirror::render (Shader &shader)
{
    glm::mat4 model(1.0f);

    model = glm::rotate(model, (float)M_PI/6, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.49f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(2,2,2));
    shader.setUniform("model", model);
    mesh->render();
}
