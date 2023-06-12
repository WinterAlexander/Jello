//
// Created by Alexander Winter on 2023-01-19.
//

#include <stdexcept>
#include <fstream>
#include <sstream>
#include "asset/ShaderAsset.h"

using namespace jello;

ShaderAsset::ShaderAsset(std::string vertexPath,
                         std::string fragmentPath)
    : vertexPath(std::move(vertexPath)), 
      fragmentPath(std::move(fragmentPath)), 
      name(this->vertexPath + " - " + this->fragmentPath),
      hashCode(std::hash<std::string>{}(name)) {
}

const void* ShaderAsset::load() const {
    std::ifstream vsSourceFile(vertexPath);
    std::ifstream fsSourceFile(fragmentPath);

    if(!vsSourceFile.good() || !fsSourceFile.good())
        throw std::runtime_error("Shader file(s) not found");

    std::stringstream buffer;
    buffer << vsSourceFile.rdbuf();

    std::string vertexShaderSource = buffer.str();

    buffer.str(std::string());
    buffer.clear();
    buffer << fsSourceFile.rdbuf();

    std::string fragmentShaderSource = buffer.str();

    vsSourceFile.close();
    fsSourceFile.close();

    jello::ShaderProgram* shaderProgram = new jello::ShaderProgram(vertexShaderSource, fragmentShaderSource);
    shaderProgram->prepend("#version 330 core\n");
    shaderProgram->compile();

    return shaderProgram;
}

const std::string& ShaderAsset::getName() const {
    return name;
}

bool ShaderAsset::isEquivalentTo(const AssetBase* asset) const {
    if(const ShaderAsset* shaderAsset = dynamic_cast<const ShaderAsset*>(asset)) {
        return shaderAsset->vertexPath == vertexPath 
            && shaderAsset->fragmentPath == fragmentPath;
    }
    
    return false;
}

size_t ShaderAsset::getHashCode() const {
    return hashCode;
}
