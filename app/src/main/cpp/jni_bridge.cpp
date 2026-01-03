#include <jni.h>
#include <android/asset_manager_jni.h>
#include "Engine.h"

using namespace RacingEngine;

static Engine* g_engine = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeInit(
    JNIEnv* env, jobject /* this */, jobject assetManager) {
    
    if (g_engine == nullptr) {
        g_engine = new Engine();
    }
    
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    g_engine->initialize(mgr);
}

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeResize(
    JNIEnv* env, jobject /* this */, jint width, jint height) {
    
    if (g_engine != nullptr) {
        g_engine->resize(width, height);
    }
}

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeUpdate(
    JNIEnv* env, jobject /* this */, jfloat deltaTime) {
    
    if (g_engine != nullptr) {
        g_engine->update(deltaTime);
    }
}

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeRender(
    JNIEnv* env, jobject /* this */) {
    
    if (g_engine != nullptr) {
        g_engine->render();
    }
}

} // extern "C"