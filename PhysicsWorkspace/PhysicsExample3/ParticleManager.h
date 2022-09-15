#pragma once

#include "Particle.h"

#include <vector>

class ParticleManager {
public:
	ParticleManager();
	~ParticleManager();

	Particle& CreateParticle(const Vector3& position);
	void Integrate(float duration);

private:
	std::vector<Particle> m_Particles;
};