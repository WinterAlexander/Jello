//
// Created by Alexander Winter on 2023-02-02.
//

#ifndef JELLO_MESHRENDERER_H
#define JELLO_MESHRENDERER_H

#include <vector>
#include <map>
#include "Vertex.h"
#include "render/Texture.h"
#include "render/ShaderProgram.h"
#include "MeshTexture.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"

namespace jello {
	class MeshRenderer;
}

class jello::MeshRenderer {
	const std::vector<jello::Vertex> vertices;
    const std::vector<unsigned int> indices;
    const std::vector<jello::MeshTexture> textures;

	unsigned int vao, vbo, ebo;
public:
    MeshRenderer(const aiMesh* mesh, const aiScene* scene);
    
	MeshRenderer(std::vector<jello::Vertex> vertices,
                 std::vector<unsigned int> indices,
                 std::vector<jello::MeshTexture> textures);

	void draw(jello::ShaderProgram& shader);
    
private:
    void initBuffers();
    
    static std::vector<jello::Vertex> loadVertices(const aiMesh* mesh);
    
    static std::vector<unsigned int> loadIndices(const aiMesh* mesh);
    
    static std::vector<jello::MeshTexture> loadTextures(const aiMesh* mesh, const aiScene* scene);
};


#endif //JELLO_MESHRENDERER_H
