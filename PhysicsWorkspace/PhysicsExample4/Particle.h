#pragma once

#include "Vector3.h"

class Particle {
	// Private area
public:
	Particle();
	~Particle();
	Particle(const Particle& particle);
	Particle operator=(const Particle& particle);

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	float age;

	float damping;
	float mass;

	void PrintInfo();

	void Integrate(float dt);
};