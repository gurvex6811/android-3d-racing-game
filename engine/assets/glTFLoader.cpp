#include "glTFLoader.h"
#include <cstring>
#include <android/log.h>

#define LOG_TAG "glTFLoader"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace RacingEngine {

glTFModel glTFLoader::parse(const unsigned char* data, size_t size) {
    glTFModel model;
    model.valid = false;

    if (size < 12) {
        LOGE("File too small for glTF binary");
        return model;
    }

    // Verify glB header: magic "glTF" (0x46546C67)
    uint32_t magic;
    memcpy(&magic, data, 4);
    if (magic != 0x46546C67) {
        LOGE("Not a valid glTF binary (bad magic)");
        return model;
    }

    uint32_t version;
    memcpy(&version, data + 4, 4);
    if (version != 2) {
        LOGE("Unsupported glTF version: %u", version);
        return model;
    }

    uint32_t totalLength;
    memcpy(&totalLength, data + 8, 4);

    // Parse chunks
    size_t offset = 12;
    std::vector<unsigned char> jsonData;
    std::vector<unsigned char> binData;

    while (offset + 8 <= size) {
        uint32_t chunkLength;
        uint32_t chunkType;
        memcpy(&chunkLength, data + offset, 4);
        memcpy(&chunkType, data + offset + 4, 4);
        offset += 8;

        if (offset + chunkLength > size) break;

        if (chunkType == 0x4E4F534A) { // JSON
            jsonData.resize(chunkLength);
            memcpy(jsonData.data(), data + offset, chunkLength);
        } else if (chunkType == 0x004E4942) { // BIN
            binData.resize(chunkLength);
            memcpy(binData.data(), data + offset, chunkLength);
        }

        offset += chunkLength;
    }

    if (jsonData.empty()) {
        LOGE("No JSON chunk found in glTF binary");
        return model;
    }

    // Simple JSON parsing for mesh primitives
    // Extract bufferViews and accessors for POSITION, NORMAL, TEXCOORD_0, and INDICES
    std::string jsonStr((char*)jsonData.data(), jsonData.size());

    // Find meshes section
    size_t meshesPos = jsonStr.find("\"meshes\"");
    if (meshesPos == std::string::npos) {
        // Try to find primitives directly
        meshesPos = jsonStr.find("\"primitives\"");
    }
    if (meshesPos == std::string::npos) {
        LOGE("No meshes found in glTF JSON");
        return model;
    }

    // Find accessors and bufferViews arrays
    size_t accessorsPos = jsonStr.find("\"accessors\"");
    size_t bufferViewsPos = jsonStr.find("\"bufferViews\"");

    // Parse mesh primitives by finding accessor indices
    // Look for each primitive's attributes and indices
    size_t searchPos = meshesPos;
    while (true) {
        size_t primPos = jsonStr.find("\"primitives\"", searchPos);
        if (primPos == std::string::npos) break;

        // Find indices accessor
        size_t indicesPos = jsonStr.find("\"indices\"", primPos);
        size_t posAttrPos = jsonStr.find("\"POSITION\"", primPos);
        size_t normAttrPos = jsonStr.find("\"NORMAL\"", primPos);
        size_t texAttrPos = jsonStr.find("\"TEXCOORD_0\"", primPos);

        if (indicesPos == std::string::npos || posAttrPos == std::string::npos) {
            searchPos = primPos + 12;
            continue;
        }

        // Extract accessor indices by finding numbers after attribute names
        auto extractInt = [&](size_t from) -> int {
            size_t colonPos = jsonStr.find(':', from);
            if (colonPos == std::string::npos) return -1;
            size_t numStart = colonPos + 1;
            while (numStart < jsonStr.size() && (jsonStr[numStart] == ' ' || jsonStr[numStart] == '\t'))
                numStart++;
            int result = 0;
            bool found = false;
            for (size_t i = numStart; i < jsonStr.size() && i < numStart + 10; i++) {
                if (jsonStr[i] >= '0' && jsonStr[i] <= '9') {
                    result = result * 10 + (jsonStr[i] - '0');
                    found = true;
                } else if (found) break;
            }
            return found ? result : -1;
        };

        int indicesAccessor = extractInt(indicesPos);
        int posAccessor = extractInt(posAttrPos);
        int normAccessor = (normAttrPos != std::string::npos) ? extractInt(normAttrPos) : -1;
        int texAccessor = (texAttrPos != std::string::npos) ? extractInt(texAttrPos) : -1;

        // Parse accessor details to get bufferView offsets
        // For each accessor, find its bufferView, byteOffset, count, and componentType
        auto getAccessorInfo = [&](int accessorIndex, int& bvIndex, int& byteOffset, int& count, int& componentType, std::string& typeStr) -> bool {
            // Find accessor at index accessorIndex
            size_t accStart = accessorsPos;
            for (int i = 0; i <= accessorIndex; i++) {
                accStart = jsonStr.find('{', accStart + 1);
                if (accStart == std::string::npos) return false;
            }
            size_t accEnd = jsonStr.find('}', accStart);
            if (accEnd == std::string::npos) return false;

            std::string accStr = jsonStr.substr(accStart, accEnd - accStart + 1);

            auto findVal = [&](const std::string& key) -> int {
                size_t pos = accStr.find(key);
                if (pos == std::string::npos) return -1;
                return extractInt(accStart + pos);
            };

            bvIndex = findVal("\"bufferView\"");
            byteOffset = findVal("\"byteOffset\"");
            if (byteOffset < 0) byteOffset = 0;
            count = findVal("\"count\"");
            componentType = findVal("\"componentType\"");

            // Find type string
            size_t typePos = accStr.find("\"type\"");
            if (typePos != std::string::npos) {
                size_t quoteStart = accStr.find('"', typePos + 6);
                if (quoteStart != std::string::npos) {
                    size_t quoteEnd = accStr.find('"', quoteStart + 1);
                    if (quoteEnd != std::string::npos) {
                        typeStr = accStr.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                    }
                }
            }

            return bvIndex >= 0 && count > 0;
        };

        auto getBufferViewInfo = [&](int bvIndex, int& byteOffset, int& byteLength) -> bool {
            size_t bvStart = bufferViewsPos;
            for (int i = 0; i <= bvIndex; i++) {
                bvStart = jsonStr.find('{', bvStart + 1);
                if (bvStart == std::string::npos) return false;
            }
            size_t bvEnd = jsonStr.find('}', bvStart);
            if (bvEnd == std::string::npos) return false;

            std::string bvStr = jsonStr.substr(bvStart, bvEnd - bvStart + 1);

            byteOffset = 0;
            byteLength = 0;

            size_t offPos = bvStr.find("\"byteOffset\"");
            if (offPos != std::string::npos) {
                byteOffset = extractInt(bvStart + offPos);
            }

            size_t lenPos = bvStr.find("\"byteLength\"");
            if (lenPos != std::string::npos) {
                byteLength = extractInt(bvStart + lenPos);
            }

            return byteLength > 0;
        };

        // Read position data
        int posBV, posOff, posCount, posCompType;
        std::string posType;
        if (!getAccessorInfo(posAccessor, posBV, posOff, posCount, posCompType, posType)) {
            searchPos = primPos + 12;
            continue;
        }

        int posBVOff, posBVLen;
        getBufferViewInfo(posBV, posBVOff, posBVLen);

        // Read indices data
        int idxBV, idxOff, idxCount, idxCompType;
        std::string idxType;
        if (!getAccessorInfo(indicesAccessor, idxBV, idxOff, idxCount, idxCompType, idxType)) {
            searchPos = primPos + 12;
            continue;
        }

        int idxBVOff, idxBVLen;
        getBufferViewInfo(idxBV, idxBVOff, idxBVLen);

        // Read normal data
        int normBV = -1, normOff = 0, normCount = 0, normCompType = 0;
        std::string normType;
        int normBVOff = 0, normBVLen = 0;
        if (normAccessor >= 0) {
            getAccessorInfo(normAccessor, normBV, normOff, normCount, normCompType, normType);
            getBufferViewInfo(normBV, normBVOff, normBVLen);
        }

        // Read texcoord data
        int texBV = -1, texOff = 0, texCount = 0, texCompType = 0;
        std::string texType;
        int texBVOff = 0, texBVLen = 0;
        if (texAccessor >= 0) {
            getAccessorInfo(texAccessor, texBV, texOff, texCount, texCompType, texType);
            getBufferViewInfo(texBV, texBVOff, texBVLen);
        }

        // Build vertices
        glTFMeshPrimitive primitive;

        size_t posDataOffset = posBVOff + posOff;
        size_t idxDataOffset = idxBVOff + idxOff;
        size_t normDataOffset = (normAccessor >= 0) ? (normBVOff + normOff) : 0;
        size_t texDataOffset = (texAccessor >= 0) ? (texBVOff + texOff) : 0;

        int vertexCount = posCount / 3; // Vec3 = 3 floats per vertex
        if (vertexCount <= 0) vertexCount = posCount;

        primitive.vertices.resize(vertexCount);

        for (int v = 0; v < vertexCount; v++) {
            // Position
            if (posDataOffset + v * 12 + 12 <= binData.size()) {
                memcpy(primitive.vertices[v].position, binData.data() + posDataOffset + v * 12, 12);
            }

            // Normal
            if (normAccessor >= 0 && normDataOffset + v * 12 + 12 <= binData.size()) {
                memcpy(primitive.vertices[v].normal, binData.data() + normDataOffset + v * 12, 12);
            } else {
                primitive.vertices[v].normal[0] = 0;
                primitive.vertices[v].normal[1] = 1;
                primitive.vertices[v].normal[2] = 0;
            }

            // TexCoord
            if (texAccessor >= 0 && texDataOffset + v * 8 + 8 <= binData.size()) {
                memcpy(primitive.vertices[v].texCoord, binData.data() + texDataOffset + v * 8, 8);
            } else {
                primitive.vertices[v].texCoord[0] = 0;
                primitive.vertices[v].texCoord[1] = 0;
            }
        }

        // Indices
        if (idxCompType == 5123) { // UNSIGNED_SHORT
            for (int i = 0; i < idxCount; i++) {
                uint16_t idx;
                memcpy(&idx, binData.data() + idxDataOffset + i * 2, 2);
                primitive.indices.push_back(idx);
            }
        } else if (idxCompType == 5125) { // UNSIGNED_INT
            for (int i = 0; i < idxCount; i++) {
                uint32_t idx;
                memcpy(&idx, binData.data() + idxDataOffset + i * 4, 4);
                primitive.indices.push_back(idx);
            }
        } else if (idxCompType == 5121) { // UNSIGNED_BYTE
            for (int i = 0; i < idxCount; i++) {
                primitive.indices.push_back(binData[idxDataOffset + i]);
            }
        }

        if (!primitive.vertices.empty() && !primitive.indices.empty()) {
            model.primitives.push_back(std::move(primitive));
            model.valid = true;
        }

        searchPos = primPos + 12;
    }

    LOGI("glTF parsed: %zu primitives, valid=%d", model.primitives.size(), model.valid);
    return model;
}

} // namespace RacingEngine
