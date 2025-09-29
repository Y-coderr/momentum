#include "Particle.h"

Particle::Particle(const Eigen::Vector3f& position, float mass)
    : position(position)
    , velocity(Eigen::Vector3f::Zero())
    , force(Eigen::Vector3f::Zero())
    , mass(mass)
    , lifetime(0.0f)
    , active(true)
{
}

void Particle::Update(float deltaTime, const Eigen::Vector3f& gravity)
{
    if (!active) return;

    // Apply gravity
    force += mass * gravity;

    // Update velocity
    velocity += (force / mass) * deltaTime;

    // Update position
    position += velocity * deltaTime;

    // Clear forces for next frame
    force.setZero();

    // Update lifetime
    lifetime += deltaTime;
}

void Particle::ApplyForce(const Eigen::Vector3f& f)
{
    if (active) {
        force += f;
    }
}

void Particle::ApplyImpulse(const Eigen::Vector3f& impulse)
{
    if (active) {
        velocity += impulse / mass;
    }
}