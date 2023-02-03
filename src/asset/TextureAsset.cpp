//
// Created by Alexander Winter on 2022-02-11.
//

#include "asset/TextureAsset.h"
#include "stb_image.h"

#include <utility>
#include <stdexcept>

jello::TextureAsset::TextureAsset(std::string path)
    : SinglePathAsset(std::move(path)) {}

void* jello::TextureAsset::load() const {

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if(!data)
        throw std::runtime_error(std::string("Failed to load texture with STBI: ") + stbi_failure_reason());

    if(nrChannels != 3 && nrChannels != 4)
        throw std::runtime_error("Unsupported number of channels: " + std::to_string(nrChannels));
    
    jello::Texture* texture = new Texture(width, 
                                          height,
                                          nrChannels == 3 ? GL_RGB : GL_RGBA, 
                                          data);

    stbi_image_free(data);
    
    return texture;
}

