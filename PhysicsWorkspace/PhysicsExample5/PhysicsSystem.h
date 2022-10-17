#pragma once

#include "Particle.h"

#include <vector>

class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();

	PhysicsObject* CreateParticle(const Vector3& position);
	void UpdateStep(float duration);

private:
	std::vector<PhysicsObject*> m_Particles;
};