#pragma once

#include "Particle.h"

#include <vector>

class ParticleSystem {
public:
	ParticleSystem();
	ParticleSystem(const Vector3& position);
	~ParticleSystem();

	// Typically done during loading of a level,
	// not performed during the gameplay, as it
	// could cause performance spikes.
	void GenerateParticles(unsigned int count);

	void CreateParticle(const Vector3& velocity);
	void Integrate(float duration);
	void PrintParticleInfo();

private:
	unsigned int m_NumParticles;
	std::vector<Particle> m_Particles;
	Vector3 m_Position;
};