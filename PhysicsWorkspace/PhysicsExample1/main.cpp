#include "Vector3.h"

#include <iostream>		// for cout

void PrintVector(const Vector3 &v)
{
	std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

bool CompareVector(const Vector3& v, int x, int y, int z)
{
	if (v.x == x && v.y == y && v.z == z)
		return true;

	return false;
}

// TestVector3Implementations
// Runs functions on Vector3 to determine if
// the resulting value is correct or not.
void TestVector3Implementations()
{
	Vector3 vA(6, 9, 12);
	Vector3 vB(1, 2, 3);
	Vector3 result;

	// operator+
	result = vA + vB;
	std::cout << "vA + vB = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x + vB.x, vA.y + vB.y, vA.z + vB.z))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator-
	result = vA + vB;
	std::cout << "vA - vB = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x - vB.x, vA.y - vB.y, vA.z - vB.z))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator*
	result = vA * 3;
	std::cout << "vA * 3 = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x * 3, vA.y * 3, vA.z * 3))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator/
	result = vA / 3;
	std::cout << "vA / 3 = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x / 3, vA.y / 3, vA.z / 3))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator+=
	result = vA;
	result += vB;
	std::cout << "vA += vB = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x + vB.x, vA.y + vB.y, vA.z + vB.z))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator-=
	result = vA;
	result -= vB;
	std::cout << "vA - vB = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x - vB.x, vA.y - vB.y, vA.z - vB.z))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator*=
	result = vA;
	result *= 3;
	std::cout << "vA += vB = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x * 3, vA.y * 3, vA.z * 3))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";

	// operator/=
	result = vA;
	result /= 3;
	std::cout << "vA /= 3 = ";
	PrintVector(result);
	std::cout << "\n";
	if (CompareVector(result, vA.x / 3, vA.y / 3, vA.z / 3))
		std::cout << "Correct!\n";
	else
		std::cout << "Incorrect!\n";
}

// Main entry point to our program
int main(int argc, char** argv)
{
	TestVector3Implementations();


	// Return 0 for success
	return 0;
}