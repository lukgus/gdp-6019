#include "Particle.h"
#include <iostream>

//#define PRINT_DEBUG_INFO

PhysicsObject::PhysicsObject()
	: position(0.0f)
	, velocity(0.0f)
	, acceleration(0.0f)
	, damping(1.0f)
	, mass(1.0f)
	, age(-1.0f)
{
#ifdef PRINT_DEBUG_INFO
	printf("Particle::Particle();\n");
#endif
}

PhysicsObject::~PhysicsObject() {
#ifdef PRINT_DEBUG_INFO
	printf("Particle::~Particle();\n");
#endif
}

PhysicsObject::PhysicsObject(const PhysicsObject& particle) {
#ifdef PRINT_DEBUG_INFO
	printf("Particle::Particle(const Particle& particle);\n");
#endif
}

PhysicsObject PhysicsObject::operator=(const PhysicsObject& particle) {
#ifdef PRINT_DEBUG_INFO
	printf("Particle::operator=();\n");
#endif
	return PhysicsObject();
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
void PhysicsObject::PrintInfo() {
#ifdef PRINT_DEBUG_INFO
	std::cout << "-----------------\n";
	std::cout << "Velocity(" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")\n";
	std::cout << "Position(" << position.x << ", " << position.y << ", " << position.z << ")\n";
#endif
}

void PhysicsObject::Integrate(float dt) {
	//velocity = velocity + acceleration * dt;
	//velocity *= damping;
	//position = position + velocity * dt;

	velocity.addScaledVector(acceleration, dt);
	velocity *= damping;
	position.addScaledVector(velocity, dt);

	age -= dt;
}
