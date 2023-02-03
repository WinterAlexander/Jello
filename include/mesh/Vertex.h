//
// Created by Alexander Winter on 2023-02-02.
//

#ifndef JELLO_VERTEX_H
#define JELLO_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace jello {
	struct Vertex;
}

/**
 * Represents a vertex in a mesh, has position, normal and texture coordinates
 */
struct jello::Vertex {
	glm::vec3 position;
	glm::vec3 normal, tangent;
	glm::vec2 textureCoordinates;
};


#endif //JELLO_VERTEX_H
