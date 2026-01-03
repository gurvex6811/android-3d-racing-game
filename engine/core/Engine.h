#ifndef ENGINE_H
#define ENGINE_H

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <android/asset_manager.h>

namespace RacingEngine {

class Engine {
public:
    Engine();
    ~Engine();

    bool initialize(AAssetManager* assetManager);
    void resize(int width, int height);
    void update(float deltaTime);
    void render();
    void shutdown();

    // Input handling
    void onTouchDown(float x, float y);
    void onTouchMove(float x, float y);
    void onTouchUp(float x, float y);

private:
    int screenWidth;
    int screenHeight;
    AAssetManager* assetManager;
    
    bool isInitialized;
    float gameTime;
};

} // namespace RacingEngine

#endif // ENGINE_H