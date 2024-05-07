//
// Created by Bartek Jadczak on 28/04/2024.
//

#include "Mirror.h"

Model<PosNorTexVertex> Mirror::generateMirrorPlaneFront ()
{
    Model<PosNorTexVertex> mirrorModel;

    std::vector<PosNorTexVertex> vertices = {
            // Front face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(0, 0)},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(1,0)},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(1, 1)},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(0, 1)},

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


Model<PosNorTexVertex> Mirror::generateMirrorPlaneBack ()
{
    Model<PosNorTexVertex> mirrorModel;

    std::vector<PosNorTexVertex> vertices = {
            // Back face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},

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

Model<PosNorTexVertex> Mirror::generateMirrorPlane ()
{
    Model<PosNorTexVertex> mirrorModel;

    std::vector<PosNorTexVertex> vertices = {
            // Front face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2()},

            // Back face
            {glm::vec3(0, -0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, -0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, +0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2()},
            {glm::vec3(0, +0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2()},

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
    auto mirrorFront = generateMirrorPlaneFront();
    meshFront = std::make_unique<Mesh<PosNorTexVertex>>(mirrorFront.vertices, mirrorFront.triagleIndices);

    auto mirrorBack = generateMirrorPlaneBack();
    meshBack = std::make_unique<Mesh<PosNorTexVertex>>(mirrorBack.vertices, mirrorBack.triagleIndices);

    auto mirror = generateMirrorPlane();
    meshVolume = std::make_unique<Mesh<PosNorTexVertex>>(mirror.vertices, mirror.triagleAdjacencyIndices, GL_TRIANGLES_ADJACENCY);
}

void Mirror::render (Shader &shader)
{
    shader.setUniform("material.hasTexture", false);
    shader.setUniform("model", getModel());
    material.setupMaterial(shader);
    meshBack->render();
    transparentMaterial.setupMaterial(shader);
    meshFront->render();
}

void Mirror::renderShadow(Shader &shader) {
    shader.setUniform("model", getModel());
    meshVolume->render();
}

void Mirror::renderBack (Shader &shader)
{
    shader.setUniform("material.hasTexture", false);
    material.setupMaterial(shader);
    shader.setUniform("model", getModel());
    meshBack->render();
}

void Mirror::renderFront (Shader &shader)
{
    shader.setUniform("material.hasTexture", true);
    texture.bind(0);
    transparentMaterial.setupMaterial(shader);
    shader.setUniform("model", getModel());
    meshFront->render();
}

glm::mat4 Mirror::getModel() {
    glm::mat4 model(1.0f);
    model = glm::rotate(model, (float)M_PI/6, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3{-1.23f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(2,2,2));
    return model;
}