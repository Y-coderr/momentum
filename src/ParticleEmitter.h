#pragma once
#include "Particle.h"
#include <vector>
#include <random>

class ParticleEmitter {
public:
    ParticleEmitter(const Eigen::Vector3f& position, size_t maxParticles = 1000);
    ~ParticleEmitter() = default;

    void Update(float deltaTime, const Eigen::Vector3f& gravity);
    void Emit(size_t count);

    // Emitter properties
    void setPosition(const Eigen::Vector3f& pos) { position = pos; }
    void setDirection(const Eigen::Vector3f& dir) { direction = dir.normalized(); }
    void setSpread(float angle) { spread = angle; }
    void setSpeed(float min, float max) { minSpeed = min; maxSpeed = max; }
    void setLifetime(float min, float max) { minLifetime = min; maxLifetime = max; }
    void setParticleMass(float min, float max) { minMass = min; maxMass = max; }

    // Get particles for rendering
    const std::vector<std::unique_ptr<Particle>>& getParticles() const { return particles; }

private:
    Eigen::Vector3f position;
    Eigen::Vector3f direction;
    float spread;
    float minSpeed, maxSpeed;
    float minLifetime, maxLifetime;
    float minMass, maxMass;
    
    std::vector<std::unique_ptr<Particle>> particles;
    size_t maxParticles;
    
    std::default_random_engine randomEngine;
    std::uniform_real_distribution<float> randomFloat;
    
    Eigen::Vector3f getRandomDirection() const;
};