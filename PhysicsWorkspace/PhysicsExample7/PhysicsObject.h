#pragma once

#include "Particle.h"
#include "BoundingBox.h"

struct PhysicsObject {
public:
	Particle* particle;
	BoundingBox* boundingBox;
};