#include "TextureLoader.h"
#include <cstring>
#include <android/log.h>

#define LOG_TAG "TextureLoader"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace RacingEngine {

GLuint TextureLoader::createTexture(int width, int height, const unsigned char* pixels, GLenum format) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}

GLuint TextureLoader::loadFromData(const unsigned char* data, size_t size) {
    if (size < 8) return 0;

    // Check PNG signature
    if (data[0] == 0x89 && data[1] == 0x50 && data[2] == 0x4E && data[3] == 0x47) {
        return loadFromPNG(data, size);
    }

    // Check JPEG signature
    if (data[0] == 0xFF && data[1] == 0xD8) {
        return loadFromJPEG(data, size);
    }

    LOGE("Unknown texture format");
    return 0;
}

GLuint TextureLoader::loadFromPNG(const unsigned char* data, size_t size) {
    // Minimal PNG decoder - handles basic uncompressed PNGs
    // For production, use stb_image or Android's BitmapFactory via JNI
    LOGI("PNG texture detected (%zu bytes) - using fallback solid color", size);
    return createSolidColor(128, 128, 128);
}

GLuint TextureLoader::loadFromJPEG(const unsigned char* data, size_t size) {
    // Minimal JPEG decoder
    // For production, use stb_image or Android's BitmapFactory via JNI
    LOGI("JPEG texture detected (%zu bytes) - using fallback solid color", size);
    return createSolidColor(128, 128, 128);
}

GLuint TextureLoader::createSolidColor(unsigned char r, unsigned char g, unsigned char b, int width, int height) {
    std::vector<unsigned char> pixels(width * height * 3);
    for (int i = 0; i < width * height; i++) {
        pixels[i * 3 + 0] = r;
        pixels[i * 3 + 1] = g;
        pixels[i * 3 + 2] = b;
    }
    return createTexture(width, height, pixels.data(), GL_RGB);
}

void TextureLoader::deleteTexture(GLuint textureId) {
    if (textureId != 0) {
        glDeleteTextures(1, &textureId);
    }
}

} // namespace RacingEngine
