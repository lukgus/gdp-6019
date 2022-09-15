#include "Particle.h"
#include <iostream>

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
	velocity = velocity + acceleration * dt;
	position = position + velocity * dt;
}
