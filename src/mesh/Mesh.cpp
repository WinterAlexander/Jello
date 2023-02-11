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

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));
	glEnableVertexAttribArray(2);

	// normal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	// tangent attribute
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(4);

	glBindVertexArray(0);
}

void jello::Mesh::draw(jello::ShaderProgram& shader) {
	for(unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

		if(textures[i].type == jello::MeshTextureType::DIFFUSE)
			shader.setUniformInt("material.diffuse", i);
		else if(textures[i].type == jello::MeshTextureType::SPECULAR)
			shader.setUniformInt("material.specularMap", i);
		else if(textures[i].type == jello::MeshTextureType::NORMAL)
			shader.setUniformInt("material.normalMap", i);

		textures[i].texture.bind();
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
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

