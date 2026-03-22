#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include <cmath>

namespace RacingEngine {

struct Quaternion {
    float w, x, y, z;

    Quaternion() : w(1), x(0), y(0), z(0) {}
    Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

    static Quaternion fromAxisAngle(const Vector3& axis, float angleRad) {
        float halfAngle = angleRad * 0.5f;
        float s = sinf(halfAngle);
        Vector3 n = axis.normalized();
        return {cosf(halfAngle), n.x * s, n.y * s, n.z * s};
    }

    static Quaternion fromEuler(float pitch, float yaw, float roll) {
        float cp = cosf(pitch * 0.5f), sp = sinf(pitch * 0.5f);
        float cy = cosf(yaw * 0.5f),   sy = sinf(yaw * 0.5f);
        float cr = cosf(roll * 0.5f),   sr = sinf(roll * 0.5f);
        return {
            cr * cp * cy + sr * sp * sy,
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy
        };
    }

    Quaternion operator*(const Quaternion& q) const {
        return {
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        };
    }

    Quaternion conjugate() const { return {w, -x, -y, -z}; }

    float length() const { return sqrtf(w * w + x * x + y * y + z * z); }

    Quaternion normalized() const {
        float len = length();
        if (len < 0.00001f) return {1, 0, 0, 0};
        return {w / len, x / len, y / len, z / len};
    }

    Vector3 rotate(const Vector3& v) const {
        Quaternion qv(0, v.x, v.y, v.z);
        Quaternion result = (*this) * qv * conjugate();
        return {result.x, result.y, result.z};
    }

    void toMatrix4(float* m) const {
        float xx = x * x, yy = y * y, zz = z * z;
        float xy = x * y, xz = x * z, yz = y * z;
        float wx = w * x, wy = w * y, wz = w * z;

        m[0]  = 1.0f - 2.0f * (yy + zz);
        m[1]  = 2.0f * (xy + wz);
        m[2]  = 2.0f * (xz - wy);
        m[3]  = 0.0f;

        m[4]  = 2.0f * (xy - wz);
        m[5]  = 1.0f - 2.0f * (xx + zz);
        m[6]  = 2.0f * (yz + wx);
        m[7]  = 0.0f;

        m[8]  = 2.0f * (xz + wy);
        m[9]  = 2.0f * (yz - wx);
        m[10] = 1.0f - 2.0f * (xx + yy);
        m[11] = 0.0f;

        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[15] = 1.0f;
    }
};

} // namespace RacingEngine

#endif // QUATERNION_H
