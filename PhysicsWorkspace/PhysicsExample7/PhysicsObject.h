#pragma once

#include "Particle.h"
#include "BoundingBox.h"

struct PhysicsObject {
public:
	PhysicsObject* particle;
	BoundingBox* boundingBox;
};