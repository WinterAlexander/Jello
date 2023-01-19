//
// Created by Alexander Winter on 2022-02-11.
//

#ifndef GAMETEMPLATE_TEXTUREASSET_H
#define GAMETEMPLATE_TEXTUREASSET_H


#include <string>
#include "SinglePathAsset.h"
#include "render/Texture.h"

namespace jello {
	class TextureAsset;
}

class jello::TextureAsset : public jello::SinglePathAsset<jello::Texture> {
public:
    explicit TextureAsset(std::string path);

    [[nodiscard]] 
    void* load() const override;
};


#endif //GAMETEMPLATE_TEXTUREASSET_H
