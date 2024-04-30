//
// Created by Bartek Jadczak on 28/04/2024.
//

#include "Mirror.h"

Model Mirror::generateMirrorPlaneFront ()
{
    Model mirrorModel;

    std::vector<PositionNormalVertex> vertices = {
            // Front face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f)},

    };

    std::vector<unsigned int> triangleIndices = {
            // Back face
            0, 2, 1,
            0, 3, 2,
    };

    // Assign vertices and indices to the model
    mirrorModel.vertices = vertices;
    mirrorModel.triagleIndices = triangleIndices;

    return mirrorModel;
}

Model Mirror::generateMirrorPlaneBack ()
{
    Model mirrorModel;

    std::vector<PositionNormalVertex> vertices = {
            // Back face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},

    };

    std::vector<unsigned int> triangleIndices = {
            // Front face
            0, 1, 2,
            0, 2, 3,
    };

    // Assign vertices and indices to the model
    mirrorModel.vertices = vertices;
    mirrorModel.triagleIndices = triangleIndices;

    return mirrorModel;
}

Mirror::Mirror ()
{
    auto mirrorFront = generateMirrorPlaneFront();
    meshFront = std::make_unique<Mesh<PositionNormalVertex>>(mirrorFront.vertices, mirrorFront.triagleIndices);

    auto mirrorBack = generateMirrorPlaneBack();
    meshBack = std::make_unique<Mesh<PositionNormalVertex>>(mirrorBack.vertices, mirrorBack.triagleIndices);
}

void Mirror::render (Shader &shader)
{
    glm::mat4 model(1.0f);

    model = glm::rotate(model, (float)M_PI/6, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.49f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(2,2,2));
    shader.setUniform("model", model);
    meshBack->render();
    meshFront->render();
}

void Mirror::renderBack (Shader &shader)
{
    glm::mat4 model(1.0f);

    model = glm::rotate(model, (float)M_PI/6, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.49f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(2,2,2));
    shader.setUniform("model", model);
    meshBack->render();
}

void Mirror::renderFront (Shader &shader)
{
    glm::mat4 model(1.0f);

    model = glm::rotate(model, (float)M_PI/6, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.49f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(2,2,2));
    shader.setUniform("model", model);
    meshFront->render();
}
