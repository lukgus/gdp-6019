#include "Particle.h"
#include <iostream>

Particle::Particle()
	: position(0.0f)
	, velocity(0.0f)
	, acceleration(0.0f)
	, damping(1.0f)
	, mass(1.0f)
	, age(-1.0f)
{
	printf("Particle::Particle();\n");
}

Particle::~Particle() {
	printf("Particle::~Particle();\n");
}

Particle::Particle(const Particle& particle) {
	printf("Particle::Particle(const Particle& particle);\n");
}

Particle Particle::operator=(const Particle& particle) {
	printf("Particle::operator=();\n");
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
	std::cout << "-----------------\n";
	std::cout << "Velocity(" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")\n";
	std::cout << "Position(" << position.x << ", " << position.y << ", " << position.z << ")\n";
}

void Particle::Integrate(float dt) {
	//velocity = velocity + acceleration * dt;
	//velocity *= damping;
	//position = position + velocity * dt;

	velocity.addScaledVector(acceleration, dt);
	velocity *= damping;
	position.addScaledVector(velocity, dt);

	age -= dt;
}
