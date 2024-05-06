//
// Created by faliszewskii on 06.05.24.
//

#include "Texture.h"
#include "../Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const std::string& path) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            nrChannels==4 ? GL_SRGB_ALPHA : GL_SRGB,
            width,
            height,
            0,
            nrChannels==4 ? GL_RGBA : GL_RGB,
            GL_UNSIGNED_BYTE,
            data
    );
    glGenerateMipmap(id);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind(int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}
