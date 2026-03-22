#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix4.h"

namespace RacingEngine {

class Camera {
public:
    Camera();

    void setPerspective(float fovDeg, float aspect, float near, float far);
    void lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

    void setPosition(const Vector3& pos) { position = pos; }
    void setTarget(const Vector3& tgt) { target = tgt; }

    const Vector3& getPosition() const { return position; }
    const Vector3& getTarget() const { return target; }

    Matrix4 getViewMatrix() const;
    Matrix4 getProjectionMatrix() const;

    void followTarget(const Vector3& targetPos, const Vector3& targetForward,
                      float distance, float height, float smoothness);

private:
    Vector3 position;
    Vector3 target;
    Vector3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    Matrix4 viewMatrix;
    Matrix4 projectionMatrix;
    bool viewDirty;
    bool projDirty;
};

} // namespace RacingEngine

#endif // CAMERA_H
