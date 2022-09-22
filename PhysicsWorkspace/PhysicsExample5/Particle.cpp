#include "Particle.h"
#include <iostream>

//#define PRINT_DEBUG_INFO

Particle::Particle()
	: position(0.0f)
	, velocity(0.0f)
	, acceleration(0.0f)
	, damping(0.95f)
	, invMass(1.0f)
{
#ifdef PRINT_DEBUG_INFO
	printf("Particle::Particle();\n");
#endif
}

Particle::~Particle() {
#ifdef PRINT_DEBUG_INFO
	printf("Particle::~Particle();\n");
#endif
}

Particle::Particle(const Particle& particle) {
#ifdef PRINT_DEBUG_INFO
	printf("Particle::Particle(const Particle& particle);\n");
#endif
}

Particle Particle::operator=(const Particle& particle) {
#ifdef PRINT_DEBUG_INFO
	printf("Particle::operator=();\n");
#endif
	return Particle();
}


// NewPosition = OldPosition + Velocity * ChangeInTime
// 
// p1 = p0 + v*dt
// 
// p0 = origin position
// p1 = new position
// v  = velocity
// dt = deltatime
// 
// position = position + velocity * dt; 

// NewVelocity = OldVelocity + Acceleration * ChangeTime
//
// v1 = v0 + a * dt
// 
// a = acceleration
//
// velocity = velocity + acceleration * dt;
void Particle::PrintInfo() {
#ifdef PRINT_DEBUG_INFO
	std::cout << "-----------------\n";
	std::cout << "Velocity(" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")\n";
	std::cout << "Position(" << position.x << ", " << position.y << ", " << position.z << ")\n";
#endif
}

void Particle::Integrate(float dt) {
	//velocity = velocity + acceleration * dt;
	//velocity *= damping;
	//position = position + velocity * dt;

	// f = ma  force = mass * acceleration
	// a = f/m
	// a = f*invMass;

	// 0 or negative mass object will be a "static" object.
	if (invMass <= 0)
		return;

	acceleration = force * invMass;
	velocity.addScaledVector(acceleration, dt);

	velocity *= damping;
	position.addScaledVector(velocity, dt);
}

void Particle::ApplyForce(const Vector3& direction) {
	force += direction;
}

void Particle::KillAllForces() {
	force.Set(0.f, 0.f, 0.f);
}
