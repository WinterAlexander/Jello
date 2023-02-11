//
// Created by Alexander Winter on 2023-02-11.
//

#ifndef JELLO_SCENEASSET_H
#define JELLO_SCENEASSET_H


#include "SinglePathAsset.h"
#include "assimp/scene.h"

class SceneAsset : public jello::SinglePathAsset<const aiScene> {
	explicit SceneAsset(std::string path);

	[[nodiscard]]
	const void* load() const override;
};


#endif //JELLO_SCENEASSET_H
