#include "PhysicsUtils.h"

#include <iostream>


void SimulateTestSphereAABB() {
	Sphere sphere;
	sphere.Center.Set(0, 10, 0);
	sphere.Radius = 2.0f;

	AABB aabb;
	aabb.Min[0] = -2.f;
	aabb.Min[1] = -2.f;
	aabb.Min[2] = -2.f;
	aabb.Max[0] = 2.f;
	aabb.Max[1] = 2.f;
	aabb.Max[2] = 2.f;

	while (sphere.Center.y >= -6.0f) {
		if (TestSphereAABB(sphere, aabb)) {
			printf("Sphere at (%.2f, %.2f, %.2f) is colliding with the aabb!\n",
				sphere.Center.x, sphere.Center.y, sphere.Center.z);
		}
		else {
			printf("Sphere at (%.2f, %.2f, %.2f) is NOT colliding with the aabb!\n",
				sphere.Center.x, sphere.Center.y, sphere.Center.z);
		}

		sphere.Center.y -= 1.0f;
		system("Pause");
	}
}

void SimulateTestSphereTriangle() {
	Sphere sphere;
	sphere.Center.Set(-10, 0, 0);
	sphere.Radius = 2.0f;

	Point a(-2, 0, 0);
	Point b(2, 0, -2);
	Point c(3, 0, 1);

	Point p;

	while (sphere.Center.x >= 8.0f) {
		if (TestSphereTriangle(sphere, a, b, c, p)) {
			printf("Sphere at (%.2f, %.2f, %.2f) is COLLIDING with the triangle!\n",
				sphere.Center.x, sphere.Center.y, sphere.Center.z);
		}
		else {
			printf("Sphere at (%.2f, %.2f, %.2f) is NOT colliding with the aabb!\n",
				sphere.Center.x, sphere.Center.y, sphere.Center.z);
		}

		printf("Closest point to the sphere on the triangle is: (%.2f, %.2f, %.2f)\n",
			p.x, p.y, p.z);

		sphere.Center.x += 1.0f;
		system("Pause");
	}

}


int main(int argc, char** argv) {
	SimulateTestSphereTriangle();

	return 0;
}