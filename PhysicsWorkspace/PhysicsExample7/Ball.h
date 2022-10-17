#pragma once

#include "Particle.h"
#include "gdp/GameObject.h"

class Ball {
public:
	PhysicsObject* particle;
	gdp::GameObject* gameObject;
};