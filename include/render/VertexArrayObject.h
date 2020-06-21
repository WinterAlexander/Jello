//
// Created by Alexander Winter on 2020-06-21.
//

#ifndef JELLO_VERTEXARRAYOBJECT_H
#define JELLO_VERTEXARRAYOBJECT_H

#include <glad/glad.h>

namespace jello {
    class VertexArrayObject;
}

class jello::VertexArrayObject {
    const GLuint vaoId;

public:
    VertexArrayObject();
    VertexArrayObject(const VertexArrayObject& vao) = default;

    void bind() const;
    void unbind() const;

private:
    static GLuint genVAO();
};


#endif //JELLO_VERTEXARRAYOBJECT_H
