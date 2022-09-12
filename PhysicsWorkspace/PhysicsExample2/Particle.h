#pragma once

#include "Vector3.h"

class Particle {
	// Private area
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	void Integrate(float dt);
};