#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

namespace RacingEngine {

struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vector3 operator-(const Vector3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vector3 operator*(float s) const { return {x * s, y * s, z * s}; }
    Vector3 operator/(float s) const { float inv = 1.0f / s; return {x * inv, y * inv, z * inv}; }
    Vector3 operator-() const { return {-x, -y, -z}; }

    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }

    float length() const { return sqrtf(x * x + y * y + z * z); }
    float lengthSquared() const { return x * x + y * y + z * z; }

    Vector3 normalized() const {
        float len = length();
        if (len < 0.00001f) return {0, 0, 0};
        return {x / len, y / len, z / len};
    }

    void normalize() {
        float len = length();
        if (len > 0.00001f) { x /= len; y /= len; z /= len; }
    }

    static float dot(const Vector3& a, const Vector3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static Vector3 cross(const Vector3& a, const Vector3& b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    static Vector3 lerp(const Vector3& a, const Vector3& b, float t) {
        return a + (b - a) * t;
    }
};

inline Vector3 operator*(float s, const Vector3& v) { return v * s; }

} // namespace RacingEngine

#endif // VECTOR3_H
