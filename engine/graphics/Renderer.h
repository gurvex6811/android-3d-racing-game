#ifndef RENDERER_H
#define RENDERER_H

#include <GLES3/gl3.h>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Matrix4.h"
#include "Vector3.h"

namespace RacingEngine {

struct Renderable {
    Model* model;
    Vector3 color;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool initialize();
    void resize(int width, int height);
    void beginFrame();
    void renderModel(Model& model, const Vector3& color);
    void endFrame();
    void shutdown();

    Camera& getCamera() { return camera; }
    Shader& getShader() { return shader; }

    void setLightPosition(const Vector3& pos) { lightPosition = pos; }
    void setAmbientColor(float r, float g, float b) { ambientR = r; ambientG = g; ambientB = b; }
    void setClearColor(float r, float g, float b, float a);

    Mesh* createPlaneMesh(float width, float depth, float uvScale);
    Mesh* createCubeMesh(float size);

private:
    Shader shader;
    Camera camera;
    Vector3 lightPosition;
    float ambientR, ambientG, ambientB;
    int screenWidth, screenHeight;

    bool loadShaders();
};

} // namespace RacingEngine

#endif // RENDERER_H
