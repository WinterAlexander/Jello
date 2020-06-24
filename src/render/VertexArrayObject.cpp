//
// Created by Alexander Winter on 2020-06-21.
//

#include "render/VertexArrayObject.h"

jello::VertexArrayObject::VertexArrayObject() : vaoId(genVAO()) {

}

jello::VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &vaoId);
}

void jello::VertexArrayObject::bind() const {
    glBindVertexArray(vaoId);
}

void jello::VertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

GLuint jello::VertexArrayObject::genVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    return vao;
}
