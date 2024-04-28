//
// Created by Bartek Jadczak on 27/04/2024.
//

#include "Room.h"

Room::Room ()
{
    auto room = generateRoom(6, 6, 6);
    mesh = std::make_unique<Mesh<PositionNormalVertex>>(room.vertices, room.triagleIndices);
}

void Room::render (Shader &shader)
{
    shader.setUniform("model", glm::mat4(1));
    mesh->render();
}

Model Room::generateRoom (float width, float height, float depth)
{
    Model roomModel;

    std::vector<PositionNormalVertex> vertices = {
            // Front face
            {glm::vec3(-width / 2, -1, depth / 2), glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(width / 2, -1, depth / 2), glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(width / 2, height-1, depth / 2), glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(-width / 2, height-1, depth / 2), glm::vec3(0.0f, 0.0f, -1.0f)},

            // Back face
            {glm::vec3(-width / 2, -1, -depth / 2), glm::vec3(0.0f, 0.0f, 1.0f)},
            {glm::vec3(width / 2, -1, -depth / 2), glm::vec3(0.0f, 0.0f, 1.0f)},
            {glm::vec3(width / 2, height-1, -depth / 2), glm::vec3(0.0f, 0.0f, 1.0f)},
            {glm::vec3(-width / 2, height-1, -depth / 2), glm::vec3(0.0f, 0.0f, 1.0f)},

            // Right face
            {glm::vec3(width / 2, -1, depth / 2), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(width / 2, -1, -depth / 2), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(width / 2, height-1, -depth / 2), glm::vec3(-1.0f, 0.0f, 0.0f)},
            {glm::vec3(width / 2, height-1, depth / 2), glm::vec3(-1.0f, 0.0f, 0.0f)},

            // Left face
            {glm::vec3(-width / 2, -1, depth / 2), glm::vec3(1.0f, 0.0f, 0.0f)},
            {glm::vec3(-width / 2, -1, -depth / 2), glm::vec3(1.0f, 0.0f, 0.0f)},
            {glm::vec3(-width / 2, height-1, -depth / 2), glm::vec3(1.0f, 0.0f, 0.0f)},
            {glm::vec3(-width / 2, height-1, depth / 2), glm::vec3(1.0f, 0.0f, 0.0f)},

            // Top face
            {glm::vec3(-width / 2, height-1, depth / 2), glm::vec3(0.0f, -1.0f, 0.0f)},
            {glm::vec3(width / 2, height-1, depth / 2), glm::vec3(0.0f, -1.0f, 0.0f)},
            {glm::vec3(width / 2, height-1, -depth / 2), glm::vec3(0.0f, -1.0f, 0.0f)},
            {glm::vec3(-width / 2, height-1, -depth / 2), glm::vec3(0.0f, -1.0f, 0.0f)},

            // Bottom face
            {glm::vec3(-width / 2, -1, depth / 2), glm::vec3(0.0f, 1.0f, 0.0f)},
            {glm::vec3(width / 2, -1, depth / 2), glm::vec3(0.0f, 1.0f, 0.0f)},
            {glm::vec3(width / 2, -1, -depth / 2), glm::vec3(0.0f, 1.0f, 0.0f)},
            {glm::vec3(-width / 2, -1, -depth / 2), glm::vec3(0.0f, 1.0f, 0.0f)},


    };

    std::vector<unsigned int> triangleIndices = {
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

            // Top face
            16, 18, 17,
            18, 16, 19,

            // Bottom face
            20, 21, 22,
            22, 23, 20,

            // Define other faces similarly...
    };

    // Assign vertices and indices to the model
    roomModel.vertices = vertices;
    roomModel.triagleIndices = triangleIndices;

    return roomModel;
}
