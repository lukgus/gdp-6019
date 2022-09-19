#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
	: ParticleSystem(Vector3()) {
}

ParticleSystem::ParticleSystem(const Vector3& position)
	: m_NumParticles(0) {
	// m_Particles.reserve();
	// m_Particles.resize();
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::GenerateParticles(unsigned int count) {
	m_Particles.resize(count);
}

void ParticleSystem::CreateParticle (
	const Vector3& velocity) {
	if (m_NumParticles >= m_Particles.size()) {
		printf("ParticleSystem::CreateParticle Maximum number of particles already created!\n");
		return;
	}

	Particle& p = m_Particles[m_NumParticles];
	p.velocity = velocity;
	p.position = m_Position;
	p.age = 1.f;

	m_NumParticles++;
}

void ParticleSystem::Integrate(
	float duration) {
	for (int i = 0; i < m_Particles.size(); i++) {
		m_Particles[i].Integrate(duration);
	}
}

void ParticleSystem::PrintParticleInfo() {
	for (int i = 0; i < m_Particles.size(); i++) {
		m_Particles[i].PrintInfo();
	}
}