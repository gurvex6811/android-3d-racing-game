#ifndef GLTF_LOADER_H
#define GLTF_LOADER_H

#include <vector>
#include <string>
#include "Mesh.h"

namespace RacingEngine {

struct glTFMeshPrimitive {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

struct glTFModel {
    std::vector<glTFMeshPrimitive> primitives;
    bool valid;
};

class glTFLoader {
public:
    static glTFModel parse(const unsigned char* data, size_t size);

private:
    static void parseAccessors(const unsigned char* binData,
                               size_t accessorOffset, size_t accessorCount,
                               int componentType, const std::string& type,
                               std::vector<float>& output);
    static void parseIndices(const unsigned char* binData,
                             size_t accessorOffset, size_t accessorCount,
                             int componentType,
                             std::vector<unsigned int>& output);
};

} // namespace RacingEngine

#endif // GLTF_LOADER_H
