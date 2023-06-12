//
// Created by Alexander Winter on 2023-02-02.
//

#include "mesh/MeshRenderer.h"

#include <utility>


jello::MeshRenderer::MeshRenderer(std::vector<jello::Vertex> vertices,
                                  std::vector<unsigned int> indices,
                                  std::vector<jello::MeshTexture> textures)
	: vertices(std::move(vertices)),
	  indices(std::move(indices)),
      textures(std::move(textures)) {
    initBuffers();
}

jello::MeshRenderer::MeshRenderer(const aiMesh* mesh, 
                                  const aiScene* scene)
    : MeshRenderer(loadVertices(mesh), loadIndices(mesh), loadTextures(mesh, scene)) {}

void jello::MeshRenderer::draw(jello::ShaderProgram& shader) {
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

void jello::MeshRenderer::initBuffers() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

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

std::vector<jello::Vertex> jello::MeshRenderer::loadVertices(const aiMesh* mesh) {
    std::vector<jello::Vertex> vertices;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        jello::Vertex& vertex = vertices.emplace_back();
        vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
        vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
        
        if(mesh->mTextureCoords[0])
            vertex.textureCoordinates = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
        else
            vertex.textureCoordinates = { 0.0f, 0.0f };
        
        if(mesh->mColors[0])
            vertex.color = { mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b };
        else
            vertex.color = { 1.0f, 1.0f, 1.0f };
    }
    
    
    return vertices;
}

std::vector<unsigned int> jello::MeshRenderer::loadIndices(const aiMesh* mesh) {
    std::vector<unsigned int> indices;
    
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    return indices;
}
