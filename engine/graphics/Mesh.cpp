#include "Mesh.h"
#include "Shader.h"
#include <android/log.h>

#define LOG_TAG "Mesh"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace RacingEngine {

Mesh::Mesh() : vao(0), vbo(0), ebo(0), indexCount(0) {}

Mesh::~Mesh() {
    destroy();
}

void Mesh::upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // TexCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}

void Mesh::draw() const {
    if (vao == 0) return;
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::destroy() {
    if (vao) { glDeleteVertexArrays(1, &vao); vao = 0; }
    if (vbo) { glDeleteBuffers(1, &vbo); vbo = 0; }
    if (ebo) { glDeleteBuffers(1, &ebo); ebo = 0; }
    indexCount = 0;
}

// Model implementation
Model::Model()
    : rotationAngle(0.0f), rotationAxis(0, 1, 0), scale(1, 1, 1) {}

Model::~Model() {
    destroy();
}

void Model::addMesh(Mesh* mesh, unsigned int textureId) {
    meshes.push_back({mesh, textureId});
}

void Model::draw(const Shader& shader) const {
    Matrix4 modelMat = getModelMatrix();
    shader.setMat4("uModelMatrix", modelMat.data());

    for (const auto& entry : meshes) {
        if (entry.textureId != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, entry.textureId);
            shader.setInt("uTexture", 0);
        }
        entry.mesh->draw();
    }
}

void Model::destroy() {
    for (auto& entry : meshes) {
        if (entry.mesh) {
            entry.mesh->destroy();
            delete entry.mesh;
            entry.mesh = nullptr;
        }
    }
    meshes.clear();
}

Matrix4 Model::getModelMatrix() const {
    Matrix4 model;
    model = Matrix4::translate(position);
    if (rotationAngle != 0.0f) {
        model = model * Matrix4::rotate(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
    }
    model = model * Matrix4::scale(scale.x, scale.y, scale.z);
    return model;
}

} // namespace RacingEngine
