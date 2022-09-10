#include "Vector3.h"

// Default Constructor
// Accepts no parameters
// Returns nothing
Vector3::Vector3()
	: x(0.f)
	, y(0.f)
	, z(0.f)
{

}

// Parameterized Constructor
// Accepts a value to use for all axis
// Returns nothing
Vector3::Vector3(float value)
	: x(value)
	, y(value)
	, z(value)
{

}

// Default Constructor
// Accepts no parameters
// Returns nothing
Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{

}

// Destructor
// Accepts no parameters
// Returns nothing
Vector3::~Vector3() {

}

// Copy Constructor
// Accepts a reference to another Vector3
// returns nothing
Vector3::Vector3(const Vector3& rhs)
//: x(other.x)		This is another option instead
//, y(other.y)		of assigning all of the values
//, z(other.z)		within the constructor.
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

// Assignment Operator Overload
// Accepts a reference to another Vector3
// Returns a refernce to the new Vector3
Vector3& Vector3::operator=(const Vector3& rhs) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

// Add Operator Overload
// Accepts a reference to the right hand side of the add operation
// Returns a copy to the new Vector3
Vector3 Vector3::operator+(const Vector3& rhs) {
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

// Add Operator Overload
// Accepts a reference to the right hand side of the add operation
// Returns a copy to the new Vector3
Vector3 Vector3::operator-(const Vector3& rhs) {
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

// Add Operator Overload
// Accepts a reference to the right hand side of the add operation
// Returns a copy to the new Vector3
Vector3 Vector3::operator*(const float& scalar) {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

// Add Operator Overload
// Accepts a reference to the right hand side of the add operation
// Returns a copy to the new Vector3
Vector3 Vector3::operator/(const float& scalar) {
	return Vector3(x / scalar, y / scalar, z / scalar);
}

// Add Assignment Operator Overload
// Accepts a reference to the right hand side of the add operation
// no return, values are changed internally
void Vector3::operator+=(const Vector3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

// Subtract Assignment Operator Overload
// Accepts a reference to the right hand side of the add operation
// no return, values are changed internally
void Vector3::operator-=(const Vector3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

// Multiply Assignment Operator Overload
// Accepts a reference to the right hand side of the add operation
// no return, values are changed internally
void Vector3::operator*=(const float& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

// Division Assignment Operator Overload
// Accepts a reference to the right hand side of the add operation
// no return, values are changed internally
void Vector3::operator/=(const float& scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

