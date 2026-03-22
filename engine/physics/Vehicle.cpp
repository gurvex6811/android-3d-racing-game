#include "Vehicle.h"
#include <cmath>
#include <algorithm>

namespace RacingEngine {

Vehicle::Vehicle()
    : position(0, 0.5f, 0), velocity(0, 0, 0), acceleration(0, 0, 0),
      steeringAngle(0.0f), speed(0.0f), maxSpeed(80.0f),
      accelerationForce(40.0f), brakeForce(60.0f),
      mass(1200.0f), drag(0.98f), friction(2.0f), turnSpeed(2.5f) {
}

void Vehicle::update(float deltaTime) {
    updatePhysics(deltaTime);
}

void Vehicle::applyAcceleration(float amount) {
    amount = fmaxf(0.0f, fminf(1.0f, amount));

    // Calculate forward direction based on current heading
    float heading = atan2f(velocity.x, velocity.z);
    if (speed < 0.5f) {
        heading = steeringAngle;
    }

    float forwardX = sinf(heading);
    float forwardZ = cosf(heading);

    float force = accelerationForce * amount / mass;
    acceleration.x += forwardX * force;
    acceleration.z += forwardZ * force;
}

void Vehicle::applyBrake(float amount) {
    amount = fmaxf(0.0f, fminf(1.0f, amount));

    if (speed > 0.1f) {
        float brakeX = -(velocity.x / speed) * brakeForce * amount / mass;
        float brakeZ = -(velocity.z / speed) * brakeForce * amount / mass;
        acceleration.x += brakeX;
        acceleration.z += brakeZ;
    } else if (speed > 0) {
        // Full stop
        velocity.x = 0;
        velocity.z = 0;
    }
}

void Vehicle::applySteering(float angle) {
    steeringAngle = angle;

    // Apply steering force proportional to speed
    if (speed > 1.0f) {
        float steerForce = angle * turnSpeed * fminf(speed / maxSpeed, 1.0f);

        // Calculate perpendicular direction
        float heading = atan2f(velocity.x, velocity.z);
        float perpX = cosf(heading);
        float perpZ = -sinf(heading);

        // Don't apply lateral acceleration directly to velocity
        // Instead, rotate the velocity vector
        float rotAngle = steerForce * 0.016f; // Approximate for 60fps
        float cosA = cosf(rotAngle);
        float sinA = sinf(rotAngle);
        float newVx = velocity.x * cosA - velocity.z * sinA;
        float newVz = velocity.x * sinA + velocity.z * cosA;
        velocity.x = newVx;
        velocity.z = newVz;
    }
}

float Vehicle::getSpeed() const {
    return sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
}

void Vehicle::updatePhysics(float deltaTime) {
    // Update velocity
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;
    velocity.z += acceleration.z * deltaTime;

    // Apply drag (air resistance)
    velocity.x *= drag;
    velocity.z *= drag;

    // Apply ground friction when not accelerating
    speed = getSpeed();
    if (speed > 0.01f && acceleration.lengthSquared() < 0.001f) {
        float frictionForce = friction * deltaTime;
        if (frictionForce > speed) frictionForce = speed;
        float factor = (speed - frictionForce) / speed;
        velocity.x *= factor;
        velocity.z *= factor;
    }

    // Clamp to max speed
    clampSpeed();

    // Update position
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;

    // Keep car at ground level
    if (position.y < 0.5f) {
        position.y = 0.5f;
        velocity.y = 0;
    }

    // Reset acceleration
    acceleration = Vector3(0, 0, 0);

    // Update speed
    speed = getSpeed();
}

void Vehicle::clampSpeed() {
    float currentSpeed = getSpeed();
    if (currentSpeed > maxSpeed) {
        float scale = maxSpeed / currentSpeed;
        velocity.x *= scale;
        velocity.z *= scale;
    }
}

} // namespace RacingEngine
