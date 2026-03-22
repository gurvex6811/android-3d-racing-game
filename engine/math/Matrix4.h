#ifndef MATRIX4_H
#define MATRIX4_H

#include <cmath>
#include <cstring>
#include "Vector3.h"

namespace RacingEngine {

class Matrix4 {
public:
    float m[16];

    Matrix4() {
        identity();
    }

    void identity() {
        memset(m, 0, sizeof(m));
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }

    static Matrix4 perspective(float fov, float aspect, float near, float far) {
        Matrix4 mat;
        float tanHalfFov = tanf(fov / 2.0f);

        mat.m[0] = 1.0f / (aspect * tanHalfFov);
        mat.m[5] = 1.0f / tanHalfFov;
        mat.m[10] = -(far + near) / (far - near);
        mat.m[11] = -1.0f;
        mat.m[14] = -(2.0f * far * near) / (far - near);
        mat.m[15] = 0.0f;

        return mat;
    }

    static Matrix4 lookAt(float eyeX, float eyeY, float eyeZ,
                          float centerX, float centerY, float centerZ,
                          float upX, float upY, float upZ) {
        Matrix4 mat;

        float fx = centerX - eyeX;
        float fy = centerY - eyeY;
        float fz = centerZ - eyeZ;
        float fLen = sqrtf(fx * fx + fy * fy + fz * fz);
        fx /= fLen; fy /= fLen; fz /= fLen;

        float rx = fy * upZ - fz * upY;
        float ry = fz * upX - fx * upZ;
        float rz = fx * upY - fy * upX;
        float rLen = sqrtf(rx * rx + ry * ry + rz * rz);
        rx /= rLen; ry /= rLen; rz /= rLen;

        float ux = ry * fz - rz * fy;
        float uy = rz * fx - rx * fz;
        float uz = rx * fy - ry * fx;

        mat.m[0] = rx;  mat.m[4] = ry;  mat.m[8]  = rz;  mat.m[12] = -(rx * eyeX + ry * eyeY + rz * eyeZ);
        mat.m[1] = ux;  mat.m[5] = uy;  mat.m[9]  = uz;  mat.m[13] = -(ux * eyeX + uy * eyeY + uz * eyeZ);
        mat.m[2] = -fx; mat.m[6] = -fy; mat.m[10] = -fz; mat.m[14] = -(-fx * eyeX - fy * eyeY - fz * eyeZ);
        mat.m[3] = 0;   mat.m[7] = 0;   mat.m[11] = 0;   mat.m[15] = 1;

        return mat;
    }

    static Matrix4 translate(float x, float y, float z) {
        Matrix4 mat;
        mat.m[12] = x;
        mat.m[13] = y;
        mat.m[14] = z;
        return mat;
    }

    static Matrix4 translate(const Vector3& v) {
        return translate(v.x, v.y, v.z);
    }

    static Matrix4 scale(float x, float y, float z) {
        Matrix4 mat;
        mat.m[0]  = x;
        mat.m[5]  = y;
        mat.m[10] = z;
        return mat;
    }

    static Matrix4 scale(float s) {
        return scale(s, s, s);
    }

    static Matrix4 rotateX(float angleRad) {
        Matrix4 mat;
        float c = cosf(angleRad);
        float s = sinf(angleRad);
        mat.m[5]  = c;  mat.m[6]  = s;
        mat.m[9]  = -s; mat.m[10] = c;
        return mat;
    }

    static Matrix4 rotateY(float angleRad) {
        Matrix4 mat;
        float c = cosf(angleRad);
        float s = sinf(angleRad);
        mat.m[0]  = c;  mat.m[2]  = -s;
        mat.m[8]  = s;  mat.m[10] = c;
        return mat;
    }

    static Matrix4 rotateZ(float angleRad) {
        Matrix4 mat;
        float c = cosf(angleRad);
        float s = sinf(angleRad);
        mat.m[0] = c;  mat.m[1] = s;
        mat.m[4] = -s; mat.m[5] = c;
        return mat;
    }

    static Matrix4 rotate(float angleRad, float ax, float ay, float az) {
        float len = sqrtf(ax * ax + ay * ay + az * az);
        if (len < 0.00001f) return Matrix4();
        ax /= len; ay /= len; az /= len;

        float c = cosf(angleRad);
        float s = sinf(angleRad);
        float t = 1.0f - c;

        Matrix4 mat;
        mat.m[0]  = t * ax * ax + c;
        mat.m[1]  = t * ax * ay + s * az;
        mat.m[2]  = t * ax * az - s * ay;
        mat.m[4]  = t * ax * ay - s * az;
        mat.m[5]  = t * ay * ay + c;
        mat.m[6]  = t * ay * az + s * ax;
        mat.m[8]  = t * ax * az + s * ay;
        mat.m[9]  = t * ay * az - s * ax;
        mat.m[10] = t * az * az + c;
        return mat;
    }

    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result.m[col * 4 + row] =
                    m[0 * 4 + row] * other.m[col * 4 + 0] +
                    m[1 * 4 + row] * other.m[col * 4 + 1] +
                    m[2 * 4 + row] * other.m[col * 4 + 2] +
                    m[3 * 4 + row] * other.m[col * 4 + 3];
            }
        }
        return result;
    }

    const float* data() const { return m; }
};

} // namespace RacingEngine

#endif // MATRIX4_H
