#pragma once

#include "Vector3.h"

class PhysicsObject {
	// Private area
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	void Integrate(float dt);
};