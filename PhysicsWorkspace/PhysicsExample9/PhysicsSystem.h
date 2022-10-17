#pragma once

#include "PhysicsObject.h"

#include <vector>
#include "Spring.h"
#include "Shapes.h"

class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();

	PhysicsObject* CreatePhysicsObject(const Vector3& position, iShape* shape);
	void AddSpring(Spring* spring);
	void UpdateStep(float duration);

private:
	bool CollisionTest(const Vector3& posA, iShape* shapeA, const Vector3& posB, iShape* shapeB);
	bool CollisionTest(const Vector3& posA, Sphere* a, const Vector3& posB, Sphere* b);
	bool CollisionTest(const Vector3& posA, Sphere* a, const Vector3& posB, AABB* b);
	bool CollisionTest(const Vector3& posA, Sphere* a, const Vector3& posB, Triangle* b);

	//bool CollisionTest(AABB* a, Triangle* b);		// Not implementing
	//bool CollisionTest(AABB* a, AABB* b);			// Not implementing
	//bool CollisionTest(Triangle* a, Triangle* b);	// Not implementing

	std::vector<PhysicsObject*> m_PhysicsObjects;
	std::vector<Spring*> m_Springs;
};