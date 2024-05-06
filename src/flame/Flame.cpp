//
// Created by faliszewskii on 05.05.24.
//


#include <random>
#include "Flame.h"
#include "../Shader.h"

Flame::Flame() {
    glGenTextures(1, &noiseTextureId);
    glBindTexture(GL_TEXTURE_1D, noiseTextureId);

    float arr[TEXTURE_SIZE];
    std::mt19937 prng(std::random_device{}());
    std::chi_squared_distribution<float> dist(3);
//    std::uniform_real_distribution<float> dist(0.0, 1);
    for(int i = 0; i < TEXTURE_SIZE; i++)
        arr[i] = dist(prng);

    glTexImage1D(
            GL_TEXTURE_1D,
            0,
            GL_RED,
            TEXTURE_SIZE,
            0,
            GL_RED,
            GL_FLOAT,
            arr
    );

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
