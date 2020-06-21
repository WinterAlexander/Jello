//
// Created by Alexander Winter on 2020-06-20.
//

#include "vertex/Particle.h"

using namespace jello;

const glm::vec3& Particle::getPosition() const {
    return position;
}

const glm::vec3& Particle::getVelocity() const {
    return velocity;
}

float Particle::getMass() const {
    return mass;
}