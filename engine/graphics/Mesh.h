#ifndef MESH_H
#define MESH_H

#include <GLES3/gl3.h>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"

namespace RacingEngine {

struct Vertex {
    float position[3];
    float normal[3];
    float texCoord[2];
};

class Mesh {
public:
    Mesh();
    ~Mesh();

    void upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void draw() const;
    void destroy();

    bool isLoaded() const { return vao != 0; }

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei indexCount;
};

class Model {
public:
    Model();
    ~Model();

    void addMesh(Mesh* mesh, unsigned int textureId = 0);
    void draw(const class Shader& shader) const;
    void destroy();

    void setPosition(const Vector3& pos) { position = pos; }
    void setRotation(float angleRad, const Vector3& axis) {
        rotationAngle = angleRad;
        rotationAxis = axis;
    }
    void setScale(const Vector3& s) { scale = s; }
    void setScale(float s) { scale = Vector3(s, s, s); }

    Matrix4 getModelMatrix() const;

    const Vector3& getPosition() const { return position; }

private:
    struct MeshEntry {
        Mesh* mesh;
        unsigned int textureId;
    };

    std::vector<MeshEntry> meshes;
    Vector3 position;
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 scale;
};

} // namespace RacingEngine

#endif // MESH_H
