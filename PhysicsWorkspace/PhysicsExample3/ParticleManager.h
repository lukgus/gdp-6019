#pragma once

#include "Particle.h"

#include <vector>

class ParticleManager {
public:
	ParticleManager();
	~ParticleManager();

	PhysicsObject& CreateParticle(const Vector3& position);
	void Integrate(float duration);

private:
	std::vector<PhysicsObject> m_Particles;
};