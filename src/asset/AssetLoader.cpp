//
// Created by Alexander Winter on 2022-02-11.
//

#include <chrono>
#include "asset/AssetLoader.h"

jello::AssetLoader::AssetLoader(const Logger& logger)
    : logger(logger) {}

jello::AssetLoader::~AssetLoader() {

    for(auto const& x : map) {
        x.first->dispose(x.second);
    }
}

void jello::AssetLoader::load(const AssetBase& asset) {
    map[&asset] = nullptr;
    logger.info() << "[AssetLoader] Added " << asset.getName() << " to loading queue";
}

void jello::AssetLoader::loadAll(const std::vector<const AssetBase*>& assets) {
	for(const AssetBase* asset : assets)
		load(*asset);
}

void jello::AssetLoader::update(float millis) {

	auto duration = std::chrono::duration<float, std::milli>(millis);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	for(auto const& x : map) {

		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

		if(std::chrono::duration_cast<std::chrono::milliseconds>(now - begin) > duration)
			break;

		if(x.second != nullptr)
			continue;

		finishLoading(*x.first);
	}
}

void jello::AssetLoader::finishLoading(const AssetBase& asset) {
    if(isLoaded(asset))
        return;

    try
    {
	    const void* pointer = asset.load();

        map[&asset] = pointer;
        logger.info() << "[AssetLoader] Loaded asset " << asset.getName();
        loaded++;
    }
    catch(std::exception& ex)
    {
        logger.error() << "[AssetLoader] Failed to load asset '" 
                       << asset.getName() << "', reason: " << ex.what();
    }
}

void jello::AssetLoader::finishLoadingAll() {
	for(auto const& x : map) {
		if(x.second != nullptr)
			continue;

		finishLoading(*x.first);
	}
}

bool jello::AssetLoader::isLoaded(const AssetBase& asset) const {
    return map[&asset] != nullptr;
}

bool jello::AssetLoader::isAllLoaded() const {
	return getLoaded() == getTotal();
}

float jello::AssetLoader::getProgress() const {
    return static_cast<float>(getLoaded()) / static_cast<float>(getTotal());
}

uint32_t jello::AssetLoader::getLoaded() const {
    return loaded;
}

uint32_t jello::AssetLoader::getTotal() const {
    return map.size();
}