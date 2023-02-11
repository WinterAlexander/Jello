//
// Created by Alexander Winter on 2023-02-02.
//

#ifndef JELLO_MESH_H
#define JELLO_MESH_H

#include <vector>
#include <map>
#include "Vertex.h"
#include "render/Texture.h"
#include "render/ShaderProgram.h"
#include "MeshTexture.h"

namespace jello {
	class Mesh;
}

class jello::Mesh {
	const std::vector<jello::Vertex> vertices;
    const std::vector<unsigned int> indices;
    const std::vector<jello::MeshTexture> textures;

	unsigned int vao, vbo, ebo;
public:
	Mesh(std::vector<jello::Vertex> vertices,
		 std::vector<unsigned int> indices,
         std::vector<jello::MeshTexture> textures);

	void draw(jello::ShaderProgram& shader);

	[[nodiscard]]
	const std::vector<jello::Vertex>& getVertices() const;

	[[nodiscard]]
	const std::vector<unsigned int>& getIndices() const;

    [[nodiscard]]
    const std::vector<jello::MeshTexture>& getTextures() const;
};


#endif //JELLO_MESH_H
