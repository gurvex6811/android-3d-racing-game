#ifndef VEHICLE_H
#define VEHICLE_H

namespace RacingEngine {

struct Vector3 {
    float x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

class Vehicle {
public:
    Vehicle();
    
    void update(float deltaTime);
    void applyAcceleration(float amount);
    void applyBrake(float amount);
    void applySteering(float angle);
    
    Vector3 getPosition() const { return position; }
    Vector3 getVelocity() const { return velocity; }
    float getSpeed() const;
    
private:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    
    float steeringAngle;
    float speed;
    float maxSpeed;
    float accelerationForce;
    float brakeForce;
    float mass;
    float drag;
    
    void updatePhysics(float deltaTime);
};

} // namespace RacingEngine

#endif // VEHICLE_H