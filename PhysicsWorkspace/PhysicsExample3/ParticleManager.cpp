#include "ParticleManager.h"

ParticleManager::ParticleManager() {

}

ParticleManager::~ParticleManager() {

}

PhysicsObject& ParticleManager::CreateParticle(const Vector3& position) {
	
	// Assume this is a Bullet
	// f = mass * acceleration
	// f / mass = acceleration
	// gravity as acceleration 
	// gravity is -9.8 m/s^2

	PhysicsObject p;						// p is added onto the stack
	p.position = position;
	p.acceleration = Vector3(0.0f, -9.8f, 0.0f);	// Gravity
	p.mass = 0.01f;

	m_Particles.push_back(p);		
	return m_Particles[m_Particles.size()-1];
									// p will be removed from the stack
}

void ParticleManager::Integrate(float duration) {
	for (int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].position.y >= 0.f)
		{
			m_Particles[i].Integrate(duration);
			m_Particles[i].PrintInfo();
		}
	}
}