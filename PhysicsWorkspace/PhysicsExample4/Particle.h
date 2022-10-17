#pragma once

#include "Vector3.h"

class PhysicsObject {
	// Private area
public:
	PhysicsObject();
	~PhysicsObject();
	PhysicsObject(const PhysicsObject& particle);
	PhysicsObject operator=(const PhysicsObject& particle);

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