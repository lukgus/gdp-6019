#pragma once

#include "Vector3.h"

class Particle {
	// Private area
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	float damping;
	float mass;

	void PrintInfo();

	void Integrate(float dt);
};