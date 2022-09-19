#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
	: ParticleSystem(Vector3()) {
}

ParticleSystem::ParticleSystem(const Vector3& position) {
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
	//if (m_NumParticles >= m_Particles.size()) {
	//	printf("ParticleSystem::CreateParticle Maximum number of particles already created!\n");
	//	return;
	//}

	bool particleCreated = false;
	// NOTE: You can use an index to circularly loop the vector
	// instead of starting from 0.
	// lastUsedIndex;
	int i;
	for (i = 0; i < m_Particles.size(); i++) {
		Particle& p = m_Particles[i];
		if (p.age <= 0.f) {
			p.velocity = velocity;
			p.position = m_Position;
			p.age = 1.f;
			particleCreated = true;
			break;
		}
	}

	if (!particleCreated) {
		printf("ParticleSystem::CreateParticle Maximum number of particles already created!\n");
		return;
	}

	// m_NumParticles++;
}

void ParticleSystem::Integrate(
	float duration) {
	for (int i = 0; i < m_Particles.size(); i++) {
		Particle& p = m_Particles[i];
		if (p.age > 0.f) {
			p.Integrate(duration);
		}
	}
}

void ParticleSystem::PrintParticleInfo() {
	for (int i = 0; i < m_Particles.size(); i++) {
		Particle& p = m_Particles[i];
		if (p.age > 0.f) {
			p.PrintInfo();
		}
	}
}