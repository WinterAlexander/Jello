//
// Created by Alexander Winter on 2023-02-02.
//

#include "mesh/Mesh.h"

#include <utility>


jello::Mesh::Mesh(std::vector<jello::Vertex> vertices,
				  std::vector<unsigned int> indices,
				  const jello::Texture& texture,
                  const jello::Texture& normalMap,
				  const jello::Texture& specularMap)
	: vertices(std::move(vertices)),
	  indices(std::move(indices)),
	  texture(texture),
	  normalMap(normalMap),
	  specularMap(specularMap) {

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
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for(unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;
		if(name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if(name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setUniformInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
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

const jello::Texture& jello::Mesh::getTexture() const {
	return texture;
}

const jello::Texture& jello::Mesh::getNormalMap() const {
	return normalMap;
}

const jello::Texture& jello::Mesh::getSpecularMap() const {
	return specularMap;
}
