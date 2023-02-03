//
// Created by Alexander Winter on 2023-02-02.
//

#ifndef JELLO_MESH_H
#define JELLO_MESH_H

#include <vector>
#include "Vertex.h"
#include "render/Texture.h"
#include "render/ShaderProgram.h"

namespace jello {
	class Mesh;
}

class jello::Mesh {
	std::vector<jello::Vertex> vertices;
	std::vector<unsigned int> indices;
	const jello::Texture& texture;
	const jello::Texture& normalMap;
	const jello::Texture& specularMap;

	unsigned int vao, vbo, ebo;
public:
	Mesh(std::vector<jello::Vertex> vertices,
		 std::vector<unsigned int> indices,
		 const jello::Texture& texture,
		 const jello::Texture& normalMap,
		 const jello::Texture& specularMap);

	void draw(jello::ShaderProgram& shader);

	[[nodiscard]]
	const std::vector<jello::Vertex>& getVertices() const;

	[[nodiscard]]
	const std::vector<unsigned int>& getIndices() const;

	[[nodiscard]]
	const Texture& getTexture() const;

	[[nodiscard]]
	const Texture& getNormalMap() const;

	[[nodiscard]]
	const Texture& getSpecularMap() const;
};


#endif //JELLO_MESH_H
