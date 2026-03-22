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

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeOnTouchDown(
    JNIEnv* env, jobject /* this */, jfloat x, jfloat y) {

    if (g_engine != nullptr) {
        g_engine->onTouchDown(x, y);
    }
}

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeOnTouchMove(
    JNIEnv* env, jobject /* this */, jfloat x, jfloat y) {

    if (g_engine != nullptr) {
        g_engine->onTouchMove(x, y);
    }
}

JNIEXPORT void JNICALL
Java_com_racing_engine_RacingRenderer_nativeOnTouchUp(
    JNIEnv* env, jobject /* this */, jfloat x, jfloat y) {

    if (g_engine != nullptr) {
        g_engine->onTouchUp(x, y);
    }
}

JNIEXPORT jfloat JNICALL
Java_com_racing_engine_RacingRenderer_nativeGetSpeed(
    JNIEnv* env, jobject /* this */) {

    if (g_engine != nullptr) {
        return g_engine->getSpeed();
    }
    return 0.0f;
}

JNIEXPORT jint JNICALL
Java_com_racing_engine_RacingRenderer_nativeGetLap(
    JNIEnv* env, jobject /* this */) {

    if (g_engine != nullptr) {
        return g_engine->getCurrentLap();
    }
    return 0;
}

JNIEXPORT jfloat JNICALL
Java_com_racing_engine_RacingRenderer_nativeGetRaceTime(
    JNIEnv* env, jobject /* this */) {

    if (g_engine != nullptr) {
        return g_engine->getRaceTime();
    }
    return 0.0f;
}

JNIEXPORT jboolean JNICALL
Java_com_racing_engine_RacingRenderer_nativeIsFinished(
    JNIEnv* env, jobject /* this */) {

    if (g_engine != nullptr) {
        return g_engine->isRaceFinished();
    }
    return JNI_FALSE;
}

JNIEXPORT jint JNICALL
Java_com_racing_engine_RacingRenderer_nativeGetGameState(
    JNIEnv* env, jobject /* this */) {

    if (g_engine != nullptr) {
        return static_cast<jint>(g_engine->getGameState());
    }
    return 0;
}

} // extern "C"
