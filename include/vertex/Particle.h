//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_PARTICLE_H
#define JELLO_PARTICLE_H

#include "Vertex.h"

namespace jello {
    class Particle;
}

class jello::Particle : public jello::Vertex {

    glm::vec3 position;
    glm::vec3 velocity;
    float mass;

public:
    Particle() : Vertex(), velocity(0.0f), mass(1.0f) {}

    [[nodiscard]]
    const glm::vec3& getPosition() const;

    [[nodiscard]]
    const glm::vec3& getVelocity() const;

    [[nodiscard]]
    float getMass() const;
};


#endif //JELLO_PARTICLE_H
