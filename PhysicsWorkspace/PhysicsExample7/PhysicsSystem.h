#pragma once

#include "Particle.h"

#include <vector>
#include "Spring.h"

class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();

	Particle* CreateParticle(const Vector3& position);
	void AddSpring(Spring* spring);
	void UpdateStep(float duration);

private:
	std::vector<Particle*> m_Particles;
	std::vector<Spring*> m_Springs;
};