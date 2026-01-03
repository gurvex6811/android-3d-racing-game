#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <android/asset_manager.h>
#include <string>
#include <vector>

namespace RacingEngine {

struct ModelData {
    std::vector<unsigned char> data;
    size_t size;
};

class AssetLoader {
public:
    static bool initialize(AAssetManager* manager);
    static ModelData loadModel(const std::string& path);
    static std::vector<unsigned char> loadTexture(const std::string& path);
    static std::string loadConfig();
    
private:
    static AAssetManager* assetManager;
};

} // namespace RacingEngine

#endif // ASSET_LOADER_H
