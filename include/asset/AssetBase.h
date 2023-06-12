//
// Created by Alexander Winter on 2022-02-11.
//

#ifndef GAMETEMPLATE_ASSETBASE_H
#define GAMETEMPLATE_ASSETBASE_H

#include <vector>
#include <string>

namespace jello {
	class AssetBase;
}

class jello::AssetBase {
public:
    virtual ~AssetBase() = default;

    /**
     * Retrieves the list of dependencies this asset need to load before being
     * loaded
     * 
     * @return list of dependencies
     */
    [[nodiscard]]
    inline virtual std::vector<AssetBase*> findDependencies() const {
        return {};
    };
    
    /**
     * Checks if the specified other asset is equivalent to this one in terms of
     * what it loads
     * 
     * @param asset asset to compare
     * @return true if equivalent, otherwise false
     */
    [[nodiscard]]
    virtual bool isEquivalentTo(const AssetBase* asset) const = 0;
    
    /**
     * Computes the hash code for this asset, a hash number which must be equal
     * to equivalent assets
     * 
     * @return hash code for this asset 
     */
    [[nodiscard]]
    virtual std::size_t getHashCode() const = 0;
    
    /**
     * Loads the data of this asset and returns a void pointer to it. The actual
     * type of the pointer depends on the actual type of the Asset 
     * 
     * @return pointer to the data
     */
    [[nodiscard]]
    virtual const void* load() const = 0;

    /**
     * Diposes of the data previously loaded by this asset
     * 
     * @param data data to dispose 
     */
    virtual void dispose(const void* data) const = 0;

    /**
     * @return a name that represents this asset 
     */
    [[nodiscard]]
    virtual const std::string& getName() const = 0;
};


#endif //GAMETEMPLATE_ASSETBASE_H
