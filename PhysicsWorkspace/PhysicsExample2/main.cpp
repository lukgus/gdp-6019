#include "Vector3.h"

#include <iostream>

int main() {
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

	return 0;
}