#pragma once
#include <vector>
#include <memory>
#include <random>
#include <Eigen/Dense>
#include "PhysicsBody.h"

class Particle {
public:
    Particle(const Eigen::Vector3f& pos, const Eigen::Vector3f& vel, float mass, float lifetime)
        : position(pos), velocity(vel), mass(mass), lifetime(lifetime), currentLifetime(lifetime) {}

    void update(float deltaTime) {
        position += velocity * deltaTime;
        currentLifetime -= deltaTime;
    }

    bool isAlive() const { return currentLifetime > 0.0f; }
    const Eigen::Vector3f& getPosition() const { return position; }
    const Eigen::Vector3f& getVelocity() const { return velocity; }
    float getMass() const { return mass; }
    float getLifetime() const { return lifetime; }
    float getCurrentLifetime() const { return currentLifetime; }

private:
    Eigen::Vector3f position;
    Eigen::Vector3f velocity;
    float mass;
    float lifetime;
    float currentLifetime;
};

class ParticleEmitter {
public:
    ParticleEmitter(const Eigen::Vector3f& pos)
        : position(pos), direction(0.0f, 1.0f, 0.0f),
          spread(0.5f), 
          minSpeed(1.0f), maxSpeed(5.0f),
          minLifetime(1.0f), maxLifetime(3.0f),
          minMass(0.1f), maxMass(1.0f),
          emitInterval(0.1f), timeSinceLastEmit(0.0f) {}

    void update(float deltaTime) {
        // Update existing particles
        for (auto it = particles.begin(); it != particles.end();) {
            it->update(deltaTime);
            if (!it->isAlive()) {
                it = particles.erase(it);
            } else {
                ++it;
            }
        }

        // Emit new particles
        timeSinceLastEmit += deltaTime;
        if (timeSinceLastEmit >= emitInterval) {
            emit(10); // Emit 10 particles by default
            timeSinceLastEmit = 0.0f;
        }
    }

    void emit(int count) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        for (int i = 0; i < count; ++i) {
            // Generate random direction within spread cone
            Eigen::Vector3f randomDir = getRandomDirection();
            float speed = minSpeed + dist(gen) * (maxSpeed - minSpeed);
            float lifetime = minLifetime + dist(gen) * (maxLifetime - minLifetime);
            float mass = minMass + dist(gen) * (maxMass - minMass);

            particles.emplace_back(position, randomDir * speed, mass, lifetime);
        }
    }

    void setPosition(const Eigen::Vector3f& pos) { position = pos; }
    void setDirection(const Eigen::Vector3f& dir) { direction = dir.normalized(); }
    void setSpread(float angle) { spread = angle; }
    void setSpeed(float min, float max) { minSpeed = min; maxSpeed = max; }
    void setLifetime(float min, float max) { minLifetime = min; maxLifetime = max; }
    void setParticleMass(float min, float max) { minMass = min; maxMass = max; }

    const Eigen::Vector3f& getPosition() const { return position; }
    const std::vector<Particle>& getParticles() const { return particles; }

private:
    Eigen::Vector3f getRandomDirection() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        Eigen::Vector3f up(0.0f, 1.0f, 0.0f);
        Eigen::Vector3f right = direction.cross(up).normalized();
        if (right.norm() < 0.001f) {
            right = Eigen::Vector3f(1.0f, 0.0f, 0.0f);
        }
        Eigen::Vector3f forward = right.cross(direction).normalized();

        float theta = dist(gen) * 2.0f * M_PI; // Azimuthal angle
        float phi = dist(gen) * spread; // Polar angle (within spread cone)

        float x = sin(phi) * cos(theta);
        float y = sin(phi) * sin(theta);
        float z = cos(phi);

        return (direction * z + right * x + forward * y).normalized();
    }

    Eigen::Vector3f position;
    Eigen::Vector3f direction;
    float spread;
    float minSpeed, maxSpeed;
    float minLifetime, maxLifetime;
    float minMass, maxMass;
    float emitInterval;
    float timeSinceLastEmit;
    std::vector<Particle> particles;
};


#include <Eigen/Dense>
//eigen sparrse is used in ml sine most pos is 0

class Particles
{

};

