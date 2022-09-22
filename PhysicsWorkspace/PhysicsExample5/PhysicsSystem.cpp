#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {
}

PhysicsSystem::~PhysicsSystem() {
	for (int i = 0; i < m_Particles.size(); i++) {
		delete m_Particles[i];
	}
	// delete[] m_Particles[0];		Can check if this works (Not sure)
}

Particle* PhysicsSystem::CreateParticle(const Vector3& position) {
	Particle* particle = new Particle(position);
	m_Particles.push_back(particle);
	return particle;
}

void PhysicsSystem::UpdateStep(float duration) {
	size_t numParticles = m_Particles.size();

	for (int i = 0; i < numParticles; i++) {
		m_Particles[i]->ApplyForce(Vector3(0, -9.81f, 0));
	}

	for (int i = 0; i < numParticles; i++) {
		m_Particles[i]->Integrate(duration);

	}

	for (int i = 0; i < numParticles; i++) {
		m_Particles[i]->KillAllForces();
	}
}