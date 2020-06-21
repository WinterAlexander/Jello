//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_MODEL_H
#define JELLO_MODEL_H

#include <mesh/Mesh.h>
#include <memory>
#include "Renderable.h"

namespace jello {
    class Model;
}

class jello::Model : public Renderable {
    const std::shared_ptr<Mesh> mesh;

public:
    Model(std::shared_ptr<Mesh> mesh) : mesh(mesh) {}

    void render() override;
};


#endif //JELLO_MODEL_H
