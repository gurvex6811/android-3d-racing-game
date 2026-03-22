#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <GLES3/gl3.h>
#include <vector>
#include <string>

namespace RacingEngine {

class TextureLoader {
public:
    static GLuint loadFromData(const unsigned char* data, size_t size);
    static GLuint loadFromPNG(const unsigned char* data, size_t size);
    static GLuint loadFromJPEG(const unsigned char* data, size_t size);
    static GLuint createSolidColor(unsigned char r, unsigned char g, unsigned char b, int width = 4, int height = 4);
    static void deleteTexture(GLuint textureId);

private:
    static GLuint createTexture(int width, int height, const unsigned char* pixels, GLenum format);
};

} // namespace RacingEngine

#endif // TEXTURE_LOADER_H
