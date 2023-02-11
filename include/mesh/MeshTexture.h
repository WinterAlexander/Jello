//
// Created by Alexander Winter on 2023-02-09.
//

#ifndef JELLO_MESHTEXTURE_H
#define JELLO_MESHTEXTURE_H

#include "render/Texture.h"

namespace jello {
    enum MeshTextureType {
        DIFFUSE,
        NORMAL,
        SPECULAR
    };
    
    struct MeshTexture;
}

struct jello::MeshTexture {
    const jello::Texture& texture;
    const jello::MeshTextureType type;
};


#endif //JELLO_MESHTEXTURE_H
