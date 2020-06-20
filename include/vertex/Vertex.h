//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_VERTEX_H
#define JELLO_VERTEX_H

#include <glm/vec3.hpp>

namespace jello {
    class Vertex;
}

class jello::Vertex {
public:
    virtual ~Vertex() = default;
    [[nodiscard]]
    virtual const glm::vec3& getPosition() const = 0;
};


#endif //JELLO_VERTEX_H
