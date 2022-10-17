#include "ParticleManager.h"
#include <iostream>
#include <cmath>

class Tank {
public:
	Tank() : position(0.0f), radius(1.0f) {}
	~Tank() {}

	Vector3 position;
	float radius;
};

void ParticleManagerExample(int xVelocity, int yVelocity) {
	Tank enemyTank;
	enemyTank.position = Vector3(80.f, 0.0f, 0.0f);
	enemyTank.radius = 2;	// [78.0f, 82.f]

	ParticleManager particleManager;

	PhysicsObject& p = particleManager.CreateParticle(Vector3(0, 1, 0));
	p.velocity = Vector3((float)xVelocity, (float)yVelocity, 0);

	// Cannon ----->

	for (int i = 0; i < 100; i++)
		particleManager.Integrate(0.01f);

	// use abs to ensure we have a positive result.
	//  a+b  ===  b+a
	//  a-b  =/=  c-b
	// |a-b| === |b-a|
	float distanceToTarget = abs(enemyTank.position.x - p.position.x);

	// enemyTank.position.x = 60
	// p.position.x = 80
	// distanceToTarget = 60 - 80 = -20
	// distanceToTarget <= enemyTank.radius -20 <= radius 2

	std::cout << "-------------\n\n";

	if (distanceToTarget <= enemyTank.radius) {
		std::cout << "Direct hit!\n";
	}
	else {
		std::cout << "Landed at '" << p.position.x << "' Missed by " 
			<< distanceToTarget << " meters!\n";
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Requires x and y velocity!\n";
		return 1;
	}

	//	argv[0]			   argv[1]	argv[2]
	// PhysicsExample3.exe 100		1

	int xVelocity, yVelocity;
	sscanf_s(argv[1], "%d", &xVelocity);
	sscanf_s(argv[2], "%d", &yVelocity);

	ParticleManagerExample(xVelocity, yVelocity);

	return 0;
}