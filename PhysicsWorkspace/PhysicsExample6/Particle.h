#pragma once

#include "Vector3.h"

class Particle {
	// Private area
public:
	Particle();
	Particle(const Vector3& position);
	~Particle();
	Particle(const Particle& particle);
	Particle operator=(const Particle& particle);

	void SetMass(float mass) {
		// If the mass is 0 or less we treat it as 
		// a static 
		if (mass <= 0) {
			m_IsStatic = true;
			invMass = -1.f;
		}

		m_IsStatic = false;
		invMass = 1.f / mass;
	}

	void Integrate(float dt);
	void ApplyForce(const Vector3& direction);
	void KillAllForces();

	inline const Vector3& GetPosition() const {	return position; }
	inline const Vector3& GetVelocity() const {	return velocity; }
	inline const Vector3& GetAcceleration() const {	return acceleration; }

private:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	Vector3 force;
	float damping;

	bool m_IsStatic;
	float invMass;

	void PrintInfo();

};