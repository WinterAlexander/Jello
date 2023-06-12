//
// Created by Alexander Winter on 2022-02-11.
//

#ifndef GAMETEMPLATE_ASSETLOADER_H
#define GAMETEMPLATE_ASSETLOADER_H


#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include "Asset.h"
#include "logging/Logger.h"

namespace jello {
	class AssetLoader;

    struct AssetHash {
        std::size_t operator()(const AssetBase*& asset) const noexcept {
            return asset->getHashCode();
        }
    };
}

class jello::AssetLoader {
    const Logger& logger;

    mutable std::unordered_map<const AssetBase*, const void*> map;

    uint32_t loaded = 0;
public:
    AssetLoader(const Logger& logger);

    AssetLoader(const AssetLoader&) = delete;

    virtual ~AssetLoader();

    void load(const AssetBase& asset);

	void loadAll(const std::vector<const AssetBase*>& assets);

	void update(float millis);

    void finishLoading(const AssetBase& asset);

	void finishLoadingAll();

    const void* get(const AssetBase& asset) const {
        return map[&asset];    
    }
    
    template<class T>
    T* get(const Asset<T>& asset) const {
	    const void* pointer = map[&asset];

        if(pointer == nullptr)
            throw std::invalid_argument("Asset " + asset.getName() + " not loaded");

        return const_cast<T*>(static_cast<const T*>(pointer));
    }

    bool isLoaded(const AssetBase& asset) const;

	bool isAllLoaded() const;

    float getProgress() const;

    uint32_t getLoaded() const;

    uint32_t getTotal() const;
};


#endif //GAMETEMPLATE_ASSETLOADER_H
