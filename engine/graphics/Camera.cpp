#include "Camera.h"
#include <cmath>

namespace RacingEngine {

Camera::Camera()
    : position(0, 5, 10), target(0, 0, 0), up(0, 1, 0),
      fov(60.0f * 3.14159265f / 180.0f), aspectRatio(16.0f / 9.0f),
      nearPlane(0.1f), farPlane(1000.0f),
      viewDirty(true), projDirty(true) {}

void Camera::setPerspective(float fovDeg, float aspect, float near, float far) {
    fov = fovDeg * 3.14159265f / 180.0f;
    aspectRatio = aspect;
    nearPlane = near;
    farPlane = far;
    projDirty = true;
}

void Camera::lookAt(const Vector3& eye, const Vector3& tgt, const Vector3& upVec) {
    position = eye;
    target = tgt;
    up = upVec;
    viewDirty = true;
}

Matrix4 Camera::getViewMatrix() const {
    if (viewDirty) {
        const_cast<Camera*>(this)->viewMatrix = Matrix4::lookAt(
            position.x, position.y, position.z,
            target.x, target.y, target.z,
            up.x, up.y, up.z);
        const_cast<Camera*>(this)->viewDirty = false;
    }
    return viewMatrix;
}

Matrix4 Camera::getProjectionMatrix() const {
    if (projDirty) {
        const_cast<Camera*>(this)->projectionMatrix = Matrix4::perspective(
            fov, aspectRatio, nearPlane, farPlane);
        const_cast<Camera*>(this)->projDirty = false;
    }
    return projectionMatrix;
}

void Camera::followTarget(const Vector3& targetPos, const Vector3& targetForward,
                          float distance, float height, float smoothness) {
    Vector3 desiredPos = targetPos - targetForward * distance + Vector3(0, height, 0);
    position = Vector3::lerp(position, desiredPos, smoothness);
    target = Vector3::lerp(target, targetPos, smoothness);
    viewDirty = true;
}

} // namespace RacingEngine
