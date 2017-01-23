#ifndef QUATERNION
#define QUATERNION

#include "Vector3D.h"
//#include "matrix"

class Quaternion
{
public:

	float X;
	float Y;
	float Z;
	float W;

public:
	Quaternion() : X(0), Y(0), Z(0), W(1) {}

	Quaternion(float X, float Y, float Z, float W) : X(X), Y(Y), Z(Z), W(W) {}

	// euler angles (radians) to quaterion
	Quaternion(float X, float Y, float Z);

	// euler angles (radians) to quaterion
	Quaternion(Vector3D const& vector);

	Quaternion& Normalize();

	Quaternion& Reverse();

	Quaternion& operator=( Quaternion const& other);

	Quaternion operator+(const Quaternion& other) const;

	Quaternion operator*(const Quaternion& other) const;
	Vector3D operator*(const Vector3D& v) const;
	Quaternion operator*(float s) const;

	Quaternion& operator*=(float s);
	Quaternion& operator*=(const Quaternion& other);

	bool operator==(Quaternion const& other) const;
	bool operator!=(Quaternion const& other) const;
};

#endif // !QUATERNION
