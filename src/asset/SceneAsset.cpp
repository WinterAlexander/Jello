//
// Created by Alexander Winter on 2023-02-11.
//

#include "asset/SceneAsset.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <utility>
#include <stdexcept>

SceneAsset::SceneAsset(std::string path)
	: SinglePathAsset(std::move(path)) {}

const void* SceneAsset::load() const {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw std::runtime_error(std::string("Error loading scene with assimp: ") + importer.GetErrorString());

	return scene;
}
