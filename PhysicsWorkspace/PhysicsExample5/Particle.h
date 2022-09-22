#pragma once

#include "Vector3.h"

class Particle {
	// Private area
public:
	Particle();
	~Particle();
	Particle(const Particle& particle);
	Particle operator=(const Particle& particle);

	void ApplyForce(const Vector3& direction);

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	Vector3 force;

	float age;

	float damping;
	float mass;					// f = ma

	void PrintInfo();

	void Integrate(float dt);
};