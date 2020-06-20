//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_MESH_H
#define JELLO_MESH_H

#include "jello.h"

namespace jello {
    class Mesh;
}

class jello::Mesh {

public:
    virtual ~Mesh() = default;

    virtual int getVertexCount() const = 0;
    virtual void getVertices(float arr[]) const = 0;
};


#endif //JELLO_MESH_H
