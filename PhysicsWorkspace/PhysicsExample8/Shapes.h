#pragma once

#include "PhysicsMath.h"

struct Sphere {
	Point Center;
	float Radius;
};

struct AABB {
	// x, y, z will be indexed as 0, 1, 2 respectively
	float Min[3];
	float Max[3];
};

struct Triangle {
	Point A;
	Point B;
	Point C;
};