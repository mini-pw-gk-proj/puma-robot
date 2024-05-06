//
// Created by Bartek Jadczak on 27/04/2024.
//

#include "Room.h"

Room::Room ()
{
    generateRoom(6, 6, 6);
}

void Room::render (Shader &shader)
{
    shader.setUniform("material.hasTexture", true);
    shader.setUniform("material.texture", 0);
    material.setupMaterial(shader);
    shader.setUniform("model", glm::mat4(1));
    if(isTransparent) transparentWallTexture.bind(0);
    else wallTexture.bind(0);
    wallsMesh->render();
    floorTexture.bind(0);
    floorMesh->render();
    if(!isTransparent) {
        ceilingTexture.bind(0);
        ceilingMesh->render();
    }
}

void Room::generateRoom (float width, float height, float depth)
{
    std::vector<PosNorTexVertex> wallVertices = {
            // Front face
            {glm::vec3(-width / 2, -1, depth / 2),          glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1, 1)},
            {glm::vec3(width / 2, -1, depth / 2),           glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0, 1)},
            {glm::vec3(width / 2, height - 1, depth / 2),   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0, 0)},
            {glm::vec3(-width / 2, height - 1, depth / 2),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1, 0)},

            // Back face
            {glm::vec3(-width / 2, -1, -depth / 2),         glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0, 1)},
            {glm::vec3(width / 2, -1, -depth / 2),          glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1, 1)},
            {glm::vec3(width / 2, height - 1, -depth / 2),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1, 0)},
            {glm::vec3(-width / 2, height - 1, -depth / 2), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0, 0)},

            // Right face
            {glm::vec3(width / 2, -1, depth / 2),           glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1, 1)},
            {glm::vec3(width / 2, -1, -depth / 2),          glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0, 1)},
            {glm::vec3(width / 2, height - 1, -depth / 2),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0, 0)},
            {glm::vec3(width / 2, height - 1, depth / 2),   glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1, 0)},

            // Left face
            {glm::vec3(-width / 2, -1, depth / 2),          glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0, 1)},
            {glm::vec3(-width / 2, -1, -depth / 2),         glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1, 1)},
            {glm::vec3(-width / 2, height - 1, -depth / 2), glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1, 0)},
            {glm::vec3(-width / 2, height - 1, depth / 2),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0, 0)},
    };
    std::vector<PosNorTexVertex> ceilingVertices = {
            // Top face
            {glm::vec3(-width / 2, height - 1, depth / 2),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0, 0)},
            {glm::vec3(width / 2, height - 1, depth / 2),   glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1, 0)},
            {glm::vec3(width / 2, height - 1, -depth / 2),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1, 1)},
            {glm::vec3(-width / 2, height - 1, -depth / 2), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0, 1)},
    };
    std::vector<PosNorTexVertex> floorVertices = {
            // Bottom face
            {glm::vec3(-width / 2, -1, depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 1)},
            {glm::vec3(width / 2, -1, depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 1)},
            {glm::vec3(width / 2, -1, -depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 0)},
            {glm::vec3(-width / 2, -1, -depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 0)},
    };

    std::vector<unsigned int> wallIndices = {
            // Front face
            0, 2, 1,
            2, 0, 3,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Right face
            8, 10, 9,
            10, 8, 11,

            // Left face
            12, 13, 14,
            14, 15, 12,
    };
    std::vector<unsigned int> ceilingIndices = {
            // Top face
            0, 2, 1,
            2, 0, 3,
    };
    std::vector<unsigned int> floorIndices = {
            // Bottom face
            0, 1, 2,
            2, 3, 0,
    };

    // Assign vertices and indices to the model
    wallsMesh = std::make_unique<Mesh<PosNorTexVertex>>(wallVertices, wallIndices);
    ceilingMesh = std::make_unique<Mesh<PosNorTexVertex>>(ceilingVertices, ceilingIndices);
    floorMesh = std::make_unique<Mesh<PosNorTexVertex>>(floorVertices, floorIndices);
}
