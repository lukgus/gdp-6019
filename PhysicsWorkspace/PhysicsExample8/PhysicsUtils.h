#pragma once

#include "PhysicsMath.h"
#include "Shapes.h"

int TestSphereSphere(Sphere a, Sphere b);
float SqDistPointAABB(Point p, AABB b);
int TestSphereAABB(Sphere s, AABB b);
Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c);
int TestSphereTriangle(Sphere s, Point a, Point b, Point c, Point& p);