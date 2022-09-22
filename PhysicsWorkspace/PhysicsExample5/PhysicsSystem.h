#pragma once

#include "Particle.h"

#include <vector>

class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();

	Particle* CreateParticle();
	void UpdateStep(float duration);

private:
	std::vector<Particle*> m_Particles;
};