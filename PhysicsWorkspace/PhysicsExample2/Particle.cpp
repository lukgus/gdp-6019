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

void Particle::Integrate(float dt) {
	std::cout << "velocity = " << velocity.y << " + " << acceleration.y << " * " << dt << "\n";
	velocity = velocity + acceleration * dt;
	std::cout << "position = " << position.y << " + " << velocity.y << " * " << dt << "\n";
	position = position + velocity * dt;
}
