//
// Created by Alexander Winter on 2020-06-25.
//

#ifndef JELLO_TEXTURE_H
#define JELLO_TEXTURE_H

#include <glad/glad.h>

namespace jello {
    class Texture;
}

class jello::Texture {
    GLuint textureId;
    GLsizei width, height;

public:
    Texture(GLsizei width, GLsizei height, GLenum format, const unsigned char* data);

    ~Texture();

    void bind() const;


private:
    static GLuint genTexture();
};


#endif //JELLO_TEXTURE_H
