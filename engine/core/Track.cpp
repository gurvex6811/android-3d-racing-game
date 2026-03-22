#include "Track.h"
#include "Shader.h"
#include <cmath>
#include <android/log.h>

#define LOG_TAG "Track"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace RacingEngine {

Track::Track() : trackMesh(nullptr), barrierMesh(nullptr), checkpointMesh(nullptr), totalLaps(3) {}

Track::~Track() {
    destroy();
}

void Track::generateDefaultTrack() {
    segments.clear();
    barrierBoxes.clear();
    checkpointBoxes.clear();

    // Create an oval racing track
    const int numSegments = 32;
    const float trackWidth = 12.0f;
    const float radiusX = 80.0f;
    const float radiusZ = 50.0f;

    for (int i = 0; i < numSegments; i++) {
        float angle1 = (float)i / numSegments * 2.0f * 3.14159265f;
        float angle2 = (float)(i + 1) / numSegments * 2.0f * 3.14159265f;

        float x1 = cosf(angle1) * radiusX;
        float z1 = sinf(angle1) * radiusZ;
        float x2 = cosf(angle2) * radiusX;
        float z2 = sinf(angle2) * radiusZ;

        TrackSegment seg;
        seg.center = Vector3((x1 + x2) * 0.5f, 0, (z1 + z2) * 0.5f);
        float dx = x2 - x1;
        float dz = z2 - z1;
        seg.length = sqrtf(dx * dx + dz * dz);
        seg.width = trackWidth;
        seg.rotation = atan2f(dx, dz);
        segments.push_back(seg);
    }

    LOGI("Generated default track with %zu segments", segments.size());
    buildMesh();
}

void Track::addSegment(const TrackSegment& segment) {
    segments.push_back(segment);
}

void Track::buildMesh() {
    if (segments.empty()) return;

    destroy();
    createTrackGeometry();
    createBarriers();
}

void Track::createTrackGeometry() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < segments.size(); i++) {
        const auto& seg = segments[i];
        float hw = seg.width * 0.5f;
        float hl = seg.length * 0.5f;

        float cosR = cosf(seg.rotation);
        float sinR = sinf(seg.rotation);

        // Four corners of the segment
        Vector3 corners[4] = {
            seg.center + Vector3(-hw * cosR + hl * sinR, -0.01f, -hw * sinR - hl * cosR),
            seg.center + Vector3( hw * cosR + hl * sinR, -0.01f,  hw * sinR - hl * cosR),
            seg.center + Vector3( hw * cosR - hl * sinR, -0.01f,  hw * sinR + hl * cosR),
            seg.center + Vector3(-hw * cosR - hl * sinR, -0.01f, -hw * sinR + hl * cosR),
        };

        unsigned int baseIdx = (unsigned int)vertices.size();

        float uvSeg = (float)i;
        float uvNext = (float)(i + 1);

        vertices.push_back({{corners[0].x, corners[0].y, corners[0].z}, {0, 1, 0}, {0, uvSeg}});
        vertices.push_back({{corners[1].x, corners[1].y, corners[1].z}, {0, 1, 0}, {1, uvSeg}});
        vertices.push_back({{corners[2].x, corners[2].y, corners[2].z}, {0, 1, 0}, {1, uvNext}});
        vertices.push_back({{corners[3].x, corners[3].y, corners[3].z}, {0, 1, 0}, {0, uvNext}});

        indices.push_back(baseIdx + 0);
        indices.push_back(baseIdx + 1);
        indices.push_back(baseIdx + 2);
        indices.push_back(baseIdx + 0);
        indices.push_back(baseIdx + 2);
        indices.push_back(baseIdx + 3);
    }

    trackMesh = new Mesh();
    trackMesh->upload(vertices, indices);
    LOGI("Track mesh created with %zu vertices", vertices.size());
}

void Track::createBarriers() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    barrierBoxes.clear();

    float barrierHeight = 2.0f;
    float barrierThickness = 0.5f;

    for (size_t i = 0; i < segments.size(); i++) {
        const auto& seg = segments[i];
        float hw = seg.width * 0.5f;
        float hl = seg.length * 0.5f;

        float cosR = cosf(seg.rotation);
        float sinR = sinf(seg.rotation);

        // Left and right barrier positions
        for (int side = -1; side <= 1; side += 2) {
            float offset = (float)side * (hw + barrierThickness * 0.5f);

            Vector3 bCenter = seg.center + Vector3(offset * cosR, barrierHeight * 0.5f, offset * sinR);

            BoundingBox box;
            box.min = bCenter - Vector3(barrierThickness * 0.5f, barrierHeight * 0.5f, hl);
            box.max = bCenter + Vector3(barrierThickness * 0.5f, barrierHeight * 0.5f, hl);
            barrierBoxes.push_back(box);

            // Create a simple barrier quad (simplified for performance)
            float bCos = cosR;
            float bSin = sinR;
            float bt = barrierThickness * 0.5f;

            unsigned int baseIdx = (unsigned int)vertices.size();
            Vector3 normal((float)side * bCos, 0, (float)side * bSin);

            // Outer face of barrier
            Vector3 bCorners[4] = {
                bCenter + Vector3((float)side * bt * bCos - hl * bSin, -barrierHeight * 0.5f, (float)side * bt * bSin + hl * bCos),
                bCenter + Vector3((float)side * bt * bCos + hl * bSin, -barrierHeight * 0.5f, (float)side * bt * bSin - hl * bCos),
                bCenter + Vector3((float)side * bt * bCos + hl * bSin,  barrierHeight * 0.5f, (float)side * bt * bSin - hl * bCos),
                bCenter + Vector3((float)side * bt * bCos - hl * bSin,  barrierHeight * 0.5f, (float)side * bt * bSin + hl * bCos),
            };

            vertices.push_back({{bCorners[0].x, bCorners[0].y, bCorners[0].z}, {normal.x, normal.y, normal.z}, {0, 0}});
            vertices.push_back({{bCorners[1].x, bCorners[1].y, bCorners[1].z}, {normal.x, normal.y, normal.z}, {1, 0}});
            vertices.push_back({{bCorners[2].x, bCorners[2].y, bCorners[2].z}, {normal.x, normal.y, normal.z}, {1, 1}});
            vertices.push_back({{bCorners[3].x, bCorners[3].y, bCorners[3].z}, {normal.x, normal.y, normal.z}, {0, 1}});

            indices.push_back(baseIdx + 0);
            indices.push_back(baseIdx + 1);
            indices.push_back(baseIdx + 2);
            indices.push_back(baseIdx + 0);
            indices.push_back(baseIdx + 2);
            indices.push_back(baseIdx + 3);
        }
    }

    if (!vertices.empty()) {
        barrierMesh = new Mesh();
        barrierMesh->upload(vertices, indices);
        LOGI("Barrier mesh created with %zu vertices, %zu boxes", vertices.size(), barrierBoxes.size());
    }

    // Create checkpoint at first segment
    if (!segments.empty()) {
        const auto& seg = segments[0];
        float hw = seg.width * 0.5f;
        float cosR = cosf(seg.rotation);
        float sinR = sinf(seg.rotation);

        BoundingBox cpBox;
        cpBox.min = seg.center - Vector3(hw, 0.5f, 1.0f);
        cpBox.max = seg.center + Vector3(hw, 5.0f, 1.0f);
        checkpointBoxes.push_back(cpBox);
    }
}

void Track::draw(const Shader& shader) const {
    if (trackMesh) {
        shader.setVec3("uObjectColor", 0.4f, 0.4f, 0.4f);
        trackMesh->draw();
    }
    if (barrierMesh) {
        shader.setVec3("uObjectColor", 0.8f, 0.2f, 0.1f);
        barrierMesh->draw();
    }
}

void Track::destroy() {
    if (trackMesh) { trackMesh->destroy(); delete trackMesh; trackMesh = nullptr; }
    if (barrierMesh) { barrierMesh->destroy(); delete barrierMesh; barrierMesh = nullptr; }
    if (checkpointMesh) { checkpointMesh->destroy(); delete checkpointMesh; checkpointMesh = nullptr; }
}

bool Track::checkCollision(const Vector3& position, float radius) const {
    for (const auto& box : barrierBoxes) {
        if (position.x + radius > box.min.x && position.x - radius < box.max.x &&
            position.y + radius > box.min.y && position.y - radius < box.max.y &&
            position.z + radius > box.min.z && position.z - radius < box.max.z) {
            return true;
        }
    }
    return false;
}

bool Track::isOnTrack(const Vector3& position) const {
    for (const auto& seg : segments) {
        Vector3 diff = position - seg.center;
        float cosR = cosf(-seg.rotation);
        float sinR = sinf(-seg.rotation);
        float localX = diff.x * cosR - diff.z * sinR;
        float localZ = diff.x * sinR + diff.z * cosR;

        if (fabsf(localX) < seg.width * 0.5f && fabsf(localZ) < seg.length * 0.5f) {
            return true;
        }
    }
    return false;
}

int Track::getCheckpointIndex(const Vector3& position) const {
    for (size_t i = 0; i < checkpointBoxes.size(); i++) {
        const auto& box = checkpointBoxes[i];
        if (position.x > box.min.x && position.x < box.max.x &&
            position.z > box.min.z && position.z < box.max.z) {
            return (int)i;
        }
    }
    return -1;
}

Vector3 Track::getStartPosition() const {
    if (!segments.empty()) {
        return segments[0].center + Vector3(0, 0.5f, 0);
    }
    return Vector3(0, 0.5f, 0);
}

float Track::getStartRotation() const {
    if (!segments.empty()) {
        return segments[0].rotation;
    }
    return 0;
}

} // namespace RacingEngine
