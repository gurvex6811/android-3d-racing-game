#ifndef MATRIX4_H
#define MATRIX4_H

#include <cmath>

namespace RacingEngine {

class Matrix4 {
public:
    float m[16];

    Matrix4() {
        identity();
    }

    void identity() {
        for (int i = 0; i < 16; i++) m[i] = 0.0f;
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }

    static Matrix4 perspective(float fov, float aspect, float near, float far) {
        Matrix4 mat;
        float tanHalfFov = tan(fov / 2.0f);
        
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
        
        // Calculate forward vector
        float fx = centerX - eyeX;
        float fy = centerY - eyeY;
        float fz = centerZ - eyeZ;
        
        // Normalize forward
        float fLen = sqrt(fx*fx + fy*fy + fz*fz);
        fx /= fLen; fy /= fLen; fz /= fLen;
        
        // Calculate right vector (cross product of forward and up)
        float rx = fy * upZ - fz * upY;
        float ry = fz * upX - fx * upZ;
        float rz = fx * upY - fy * upX;
        
        // Normalize right
        float rLen = sqrt(rx*rx + ry*ry + rz*rz);
        rx /= rLen; ry /= rLen; rz /= rLen;
        
        // Calculate up vector (cross product of right and forward)
        float ux = ry * fz - rz * fy;
        float uy = rz * fx - rx * fz;
        float uz = rx * fy - ry * fx;
        
        mat.m[0] = rx;  mat.m[4] = rx;  mat.m[8]  = -fx; mat.m[12] = -(rx*eyeX + ry*eyeY + rz*eyeZ);
        mat.m[1] = ux;  mat.m[5] = uy;  mat.m[9]  = -fy; mat.m[13] = -(ux*eyeX + uy*eyeY + uz*eyeZ);
        mat.m[2] = -fx; mat.m[6] = -fy; mat.m[10] = fz;  mat.m[14] = (fx*eyeX + fy*eyeY + fz*eyeZ);
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
};

} // namespace RacingEngine

#endif // MATRIX4_H