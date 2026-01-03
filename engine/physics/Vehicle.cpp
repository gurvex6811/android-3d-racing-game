#include "Vehicle.h"
#include <cmath>

namespace RacingEngine {

Vehicle::Vehicle() 
    : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0),
      steeringAngle(0.0f), speed(0.0f), maxSpeed(100.0f),
      accelerationForce(50.0f), brakeForce(80.0f),
      mass(1200.0f), drag(0.95f) {
}

void Vehicle::update(float deltaTime) {
    updatePhysics(deltaTime);
}

void Vehicle::applyAcceleration(float amount) {
    // Apply forward force
    float forwardX = sin(steeringAngle);
    float forwardZ = cos(steeringAngle);
    
    acceleration.x += forwardX * accelerationForce * amount / mass;
    acceleration.z += forwardZ * accelerationForce * amount / mass;
}

void Vehicle::applyBrake(float amount) {
    // Apply braking force opposite to velocity
    float velocityMag = sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    if (velocityMag > 0.1f) {
        float brakeX = -(velocity.x / velocityMag) * brakeForce * amount;
        float brakeZ = -(velocity.z / velocityMag) * brakeForce * amount;
        
        acceleration.x += brakeX / mass;
        acceleration.z += brakeZ / mass;
    }
}

void Vehicle::applySteering(float angle) {
    steeringAngle = angle;
}

float Vehicle::getSpeed() const {
    return sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
}

void Vehicle::updatePhysics(float deltaTime) {
    // Update velocity
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;
    velocity.z += acceleration.z * deltaTime;
    
    // Apply drag
    velocity.x *= drag;
    velocity.y *= drag;
    velocity.z *= drag;
    
    // Update position
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;
    
    // Reset acceleration
    acceleration.x = 0;
    acceleration.y = 0;
    acceleration.z = 0;
    
    // Update speed
    speed = getSpeed();
}

} // namespace RacingEngine