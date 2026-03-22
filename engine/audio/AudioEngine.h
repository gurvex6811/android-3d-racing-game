#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <jni.h>

namespace RacingEngine {

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    void initialize(JavaVM* vm, jobject context);
    void shutdown();

    void playEngineSound(float speed);
    void stopEngineSound();
    void playBrakeSound();
    void playCollisionSound();
    void playCountdownBeep(int number);
    void playFinishSound();

    void setMasterVolume(float volume);
    void setSfxVolume(float volume);

private:
    JavaVM* javaVM;
    jobject audioHelper;
    jmethodID playSoundMethod;
    jmethodID updateEngineMethod;
    jmethodID stopEngineMethod;
    bool initialized;
};

} // namespace RacingEngine

#endif // AUDIO_ENGINE_H
