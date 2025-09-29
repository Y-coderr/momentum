#pragma once
#include <Eigen/Dense>
#include <memory>

class Particle {
public:
    Particle(const Eigen::Vector3f& position, float mass = 1.0f);
    ~Particle() = default;

    void Update(float deltaTime, const Eigen::Vector3f& gravity);
    void ApplyForce(const Eigen::Vector3f& force);
    void ApplyImpulse(const Eigen::Vector3f& impulse);

    // Getters
    const Eigen::Vector3f& getPosition() const { return position; }
    const Eigen::Vector3f& getVelocity() const { return velocity; }
    float getMass() const { return mass; }
    float getLifetime() const { return lifetime; }
    bool isActive() const { return active; }

    // Setters
    void setPosition(const Eigen::Vector3f& pos) { position = pos; }
    void setVelocity(const Eigen::Vector3f& vel) { velocity = vel; }
    void setMass(float m) { mass = m; }
    void setLifetime(float time) { lifetime = time; }
    void setActive(bool state) { active = state; }

private:
    Eigen::Vector3f position;
    Eigen::Vector3f velocity;
    Eigen::Vector3f force;
    float mass;
    float lifetime;
    bool active;
};