//
// Created by Alexander Winter on 2020-06-25.
//

#include "render/Texture.h"

jello::Texture::Texture(GLsizei width, GLsizei height, GLenum format, const unsigned char *data)
    : textureId(genTexture()), width(width), height(height) {
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

jello::Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

void jello::Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

GLuint jello::Texture::genTexture() {
    GLuint texture;
    glGenTextures(1, &texture);
    return texture;
}
