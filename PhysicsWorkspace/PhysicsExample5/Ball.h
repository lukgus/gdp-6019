#pragma once

#include "Particle.h"
#include <gdp/GameObject.h>

class Ball {
public:
	Particle* particle;
	gdp::GameObject* gameObject;
};