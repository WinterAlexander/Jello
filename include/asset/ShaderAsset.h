//
// Created by Alexander Winter on 2023-01-19.
//

#ifndef JELLO_SHADERASSET_H
#define JELLO_SHADERASSET_H


#include "SinglePathAsset.h"
#include "render/ShaderProgram.h"

namespace jello {
    class ShaderAsset;
};

class jello::ShaderAsset : public jello::Asset<jello::ShaderProgram> {
    const std::string vertexPath;
    const std::string fragmentPath;
    const std::string name;
    const size_t hashCode;
    
public:
    explicit ShaderAsset(std::string vertexPath, 
                         std::string fragmentPath);

    [[nodiscard]]
    const void* load() const override;

    [[nodiscard]]
    const std::string& getName() const override;

    bool isEquivalentTo(const AssetBase* asset) const override;

    size_t getHashCode() override;
};


#endif //JELLO_SHADERASSET_H
