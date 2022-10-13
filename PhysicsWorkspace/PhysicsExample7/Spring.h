#pragma once

#include "Particle.h"

class Spring
{
public:
	Spring(Particle* A, Particle* B, float constant, float restingLength);

	void ApplyForces(double duration);

private:
	Particle* m_ParticleA;
	Particle* m_ParticleB;
	float m_SpringConstant;
	float m_RestingLength;
};