#include <iostream>

#include "Vector3.h"
#include "Particle.h"

void VectorTest() {
	Vector3 v(2, 3, 4);
	float mag = v.Magnitude();
	std::cout << "Vector(2, 3, 4)\n";
	std::cout << "Magnitude of the vector is: " << mag << "\n";

	v.Normalize();
	std::cout << "The vector normalized is: (" <<
		v.x << ", " << v.y << ", " << v.z << ")\n";

	Vector3 invV = v.Inverse();
	std::cout << "The inverse of the normalized vector is: (" <<
		invV.x << ", " << invV.y << ", " << invV.z << ")\n";
}
void ParticleTest() {
	Particle p;
	p.position = Vector3(0.f);
	p.velocity = Vector3(0.f, 5.f, 0.f);
	p.acceleration = Vector3(0.f, -1.f, 0.f);

	while (p.position.y >= 0) {
		p.Integrate(0.1f);
		std::cout << p.position.y << "\n";
	}
}

int main() {
	ParticleTest();

	return 0;
}