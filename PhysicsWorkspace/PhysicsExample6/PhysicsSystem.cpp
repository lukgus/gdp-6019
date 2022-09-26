#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {
}

PhysicsSystem::~PhysicsSystem() {
	for (int i = 0; i < m_Particles.size(); i++) {
		delete m_Particles[i];
	}
	m_Particles.clear();

	// delete[] m_Particles[0];		Can check if this works (Not sure)
	//  -> edit: Nope, use this for array of pointers
}

Particle* PhysicsSystem::CreateParticle(const Vector3& position) {
	Particle* particle = new Particle(position);
	m_Particles.push_back(particle);
	return particle;
}

void PhysicsSystem::AddSpring(Spring* spring) {
	m_Springs.push_back(spring);
}

void PhysicsSystem::UpdateStep(float duration) {
	size_t numParticles = m_Particles.size();

	for (int i = 0; i < numParticles; i++) {
		/* Gravity */
		m_Particles[i]->ApplyForce(Vector3(0, -9.81f, 0));
	}

	for (int i = 0; i < m_Springs.size(); i++) {
		m_Springs[i]->ApplyForces(duration);
	}

	for (int i = 0; i < numParticles; i++) {
		m_Particles[i]->Integrate(duration);

	}

	for (int i = 0; i < numParticles; i++) {
		m_Particles[i]->KillAllForces();
	}
}