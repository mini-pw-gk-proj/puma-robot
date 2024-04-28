//
// Created by faliszewskii on 28.04.24.
//

#include "Skybox.h"
#include <random>

Skybox::Skybox() {
    mesh = std::make_unique<Mesh<PositionVertex>>(getVertices());
    setupCubemap();
}

void Skybox::setupCubemap() {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    for(int i = 0; i < 6; i++) {
        std::mt19937 prng(std::random_device{}());
        std::uniform_real_distribution<float> dist(0, 1);
        std::uniform_real_distribution<float> dist1(-0.15, 0);
        std::uniform_real_distribution<float> dist2(-0.05, 0);

        float arr[4*SKYBOX_SIZE*SKYBOX_SIZE];

        for (int i=0;i<SKYBOX_SIZE*SKYBOX_SIZE;i++) {
            arr[i*4+3] = 1;
            auto rnd = dist(prng);
            if(rnd > 0.999) {
                arr[i*4+0] = 1 + dist2(prng);
                arr[i*4+2] = 1 + dist2(prng);
                arr[i*4+1] = std::min(std::min(1 + dist1(prng), arr[i*4+0]), arr[i*4+2]);
            }
            else if(rnd > 0.995) {
                arr[i*4+0] = 0.9f + dist1(prng);
                arr[i*4+2] = 0.9f + dist1(prng);
                arr[i*4+1] = std::min(std::min(0.9f + dist1(prng), arr[i*4+0]), arr[i*4+2]);
            } else if(rnd > 0.98) {
                arr[i*4+0] = 0.6f + dist1(prng);
                arr[i*4+2] = 0.6f + dist1(prng);
                arr[i*4+1] = std::min(std::min(0.6f + dist1(prng), arr[i*4+0]), arr[i*4+2]);
            } else {
                arr[i*4+0] = 0;
                arr[i*4+1] = 0;
                arr[i*4+2] = 0;
            }
        }
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_SRGB_ALPHA,
                SKYBOX_SIZE,
                SKYBOX_SIZE,
                0,
                GL_RGBA,
                GL_FLOAT,
                arr
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

std::vector<PositionVertex> Skybox::getVertices() {
    return {
            {{-1.0f, 1.0f, -1.0f}},
            {{-1.0f, -1.0f, -1.0f}},
            {{1.0f, -1.0f, -1.0f}},
            {{1.0f, -1.0f, -1.0f}},
            {{1.0f, 1.0f, -1.0f}},
            {{-1.0f, 1.0f, -1.0f}},
            {{-1.0f, -1.0f, 1.0f}},
            {{-1.0f, -1.0f, -1.0f}},
            {{-1.0f, 1.0f, -1.0f}},
            {{-1.0f, 1.0f, -1.0f}},
            {{-1.0f, 1.0f, 1.0f}},
            {{-1.0f, -1.0f, 1.0f}},
            {{1.0f, -1.0f, -1.0f}},
            {{1.0f, -1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}},
            {{1.0f, 1.0f, -1.0f}},
            {{1.0f, -1.0f, -1.0f}},
            {{-1.0f, -1.0f, 1.0f}},
            {{-1.0f, 1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}},
            {{1.0f, -1.0f, 1.0f}},
            {{-1.0f, -1.0f, 1.0f}},
            {{-1.0f, 1.0f, -1.0f}},
            {{1.0f, 1.0f, -1.0f}},
            {{1.0f, 1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}},
            {{-1.0f, 1.0f, 1.0f}},
            {{-1.0f, 1.0f, -1.0f}},
            {{-1.0f, -1.0f, -1.0f}},
            {{-1.0f, -1.0f, 1.0f}},
            {{1.0f, -1.0f, -1.0f}},
            {{1.0f, -1.0f, -1.0f}},
            {{-1.0f, -1.0f, 1.0f}},
            {{1.0f, -1.0f, 1.0f}},
        };
}

void Skybox::render() {
    glDepthFunc(GL_LEQUAL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    mesh->render();
    glDepthFunc(GL_LESS);
}
