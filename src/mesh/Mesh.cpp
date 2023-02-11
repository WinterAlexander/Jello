//
// Created by Alexander Winter on 2023-02-02.
//

#include "mesh/Mesh.h"

#include <utility>


jello::Mesh::Mesh(std::vector<jello::Vertex> vertices,
				  std::vector<unsigned int> indices,
                  std::vector<jello::MeshTexture> textures)
	: vertices(std::move(vertices)),
	  indices(std::move(indices)),
      textures(std::move(textures)) {

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int),
	             &this->indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
}

void jello::Mesh::draw(jello::ShaderProgram& shader) {

}

const std::vector<jello::Vertex>& jello::Mesh::getVertices() const {
	return vertices;
}

const std::vector<unsigned int>& jello::Mesh::getIndices() const {
	return indices;
}

const std::vector<jello::MeshTexture>& jello::Mesh::getTextures() const {
    return textures;
}

