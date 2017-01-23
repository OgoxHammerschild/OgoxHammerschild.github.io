// (c) Daniel Bortfeld 2016 - 2017
#ifndef VECTOR3D
#define VECTOR3D

#include <math.h>

#define PI 3.14159265359f
#define DEGREES_TO_RADIANS(a) 2 * PI * a / 360
#define RADIANS_TO_DEGREES(r) (360 / (2 * PI)) * r

template<typename TNumber>
class TVector3D
{
public:

	TNumber X = 0;
	TNumber Y = 0;
	TNumber Z = 0;

public:

	TVector3D() {}

	TVector3D(TVector3D<int> const& other) : X(other.X), Y(other.Y), Z(other.Z) {}
	TVector3D(TVector3D<float> const& other) : X(other.X), Y(other.Y), Z(other.Z) {}

	TVector3D(TNumber const& X, TNumber const& Y, TNumber const& Z) : X(X), Y(Y), Z(Z) {}

	// Returns a Vector with X, Y and Z being 0
	static TVector3D<TNumber>& Zero();

	// Returns the Euler Angle (radians) between the specified Vectors
	static float GetAngle(TVector3D<TNumber> const& A, TVector3D<TNumber> const& B);

	// Returns the Distance between the specified Vectors
	static float GetDistance(TVector3D<TNumber> const& A, TVector3D<TNumber> const& B);

	// Returns the Dot-Product between the specified Vectors
	static float GetDotProduct(TVector3D<TNumber> const& A, TVector3D<TNumber> const& B);

	// Returns the Dot-Product between the specified Vectors
	static float GetCrossProduct(TVector3D<TNumber> const& A, TVector3D<TNumber> const& B);

	// Returns a normalized version of the Vector without changing it directly
	TVector3D<TNumber>& GetNormalized() const;

	// Normalizes the Vector
	void Normalize();

	// Returns the magnitude of the Vector (same as length)
	float& GetMagnitude() const;

	// Returns the length of the Vector (same as magnitude)
	float& GetLength() const;

	// Returns the reversed version of the Vector without changing it directly
	TVector3D<TNumber>& GetReversed() const;

	// Reverses the Vector
	void Reverse();

	// Reverses the Vector
	TVector3D<TNumber>& operator-() const;

	TVector3D<TNumber>& operator+(TVector3D<TNumber> const& other) const;
	TVector3D<TNumber>& operator-(TVector3D<TNumber> const& other) const;
	TVector3D<TNumber>& operator*(TNumber const& scalar) const;
	TVector3D<TNumber>& operator/(TNumber const& scalar) const;

	// Returns the Dot-Product of the Vectors
	float& operator*(TVector3D<TNumber> const& other) const;
	// Returns the Cross-Product of the Vectors
	TVector3D<TNumber>& operator^(TVector3D<TNumber> const& other) const;

	TVector3D<TNumber>& operator+=(TVector3D<TNumber> const& other);
	TVector3D<TNumber>& operator-=(TVector3D<TNumber> const& other);
	TVector3D<TNumber>& operator*=(TNumber const& scalar);
	TVector3D<TNumber>& operator/=(TNumber const& scalar);

	// Checks components of the vector for equality
	bool operator==(TVector3D<TNumber> const& other);
	// Checks components of the vector for inequality
	bool operator!=(TVector3D<TNumber> const& other);

};

typedef TVector3D<float> Vector3D;
typedef TVector3D<int> Vector3Di;

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::Zero()
{
	return TVector3D<TNumber>(0, 0, 0);
}

template<typename TNumber>
inline float TVector3D<TNumber>::GetAngle(TVector3D<TNumber> const & A, TVector3D<TNumber> const & B)
{
	return std::acos(DEGREES_TO_RADIANS((A*B) / (A.GetMagnitude()*B.GetMagnitude())));
}

template<typename TNumber>
inline float TVector3D<TNumber>::GetDistance(TVector3D<TNumber> const & A, TVector3D<TNumber> const & B)
{
	return (B - A).GetLength();
}

template<typename TNumber>
inline float TVector3D<TNumber>::GetDotProduct(TVector3D<TNumber> const & A, TVector3D<TNumber> const & B)
{
	return A * B;
}

template<typename TNumber>
inline float TVector3D<TNumber>::GetCrossProduct(TVector3D<TNumber> const & A, TVector3D<TNumber> const & B)
{
	return A ^ B;
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::GetNormalized() const
{
	return this / GetMagnitude();
}

template<typename TNumber>
inline void TVector3D<TNumber>::Normalize()
{
	this /= GetMagnitude();
}

template<typename TNumber>
inline float & TVector3D<TNumber>::GetMagnitude() const
{
	return std::sqrt(X*X + Y*Y + Z*Z);
}

template<typename TNumber>
inline float & TVector3D<TNumber>::GetLength() const
{
	return GetMagnitude();
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::GetReversed() const
{
	return TVector3D<TNumber>(-X, -Y, -Z);
}

template<typename TNumber>
inline void TVector3D<TNumber>::Reverse()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator-() const
{
	return GetReversed();
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator+(TVector3D<TNumber> const & other) const
{
	return TVector3D<TNumber>(X + other.X, Y + other.Y, Z + other.Z);
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator-(TVector3D<TNumber> const & other) const
{
	return TVector3D<TNumber>(X - other.X, Y - other.Y, Z - other.Z);
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator*(TNumber const & scalar) const
{
	return TVector3D<TNumber>(X * scalar, Y * scalar, Z*scalar);
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator/(TNumber const & scalar) const
{
	return TVector3D<TNumber>(X / scalar, Y / scalar, Z / scalar);
}

template<typename TNumber>
inline float & TVector3D<TNumber>::operator*(TVector3D<TNumber> const & other) const
{
	return X * other.X + Y * other.Y + Z * other.Z;
}

template<typename TNumber>
inline TVector3D<TNumber> & TVector3D<TNumber>::operator^(TVector3D<TNumber> const & other) const
{
	TNumber x = Y * other.Z - Z * other.Y;
	TNumber y = Z * other.X - X * other.Z;
	TNumber z = X * other.Y - Y * other.X;
	return TVector3D<TNumber>(x, y, z);
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator+=(TVector3D<TNumber> const & other)
{
	this = this + other;
	return *this;
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator-=(TVector3D<TNumber> const & other)
{
	this = this - other;
	return *this;
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator*=(TNumber const & scalar)
{
	this = this * scalar;
	return *this;
}

template<typename TNumber>
inline TVector3D<TNumber>& TVector3D<TNumber>::operator/=(TNumber const & scalar)
{
	this = this / scalar;
	return *this;
}

template<typename TNumber>
inline bool TVector3D<TNumber>::operator==(TVector3D<TNumber> const & other)
{
	return (X == other.X && Y == other.Y && Z == other.Z);
}

template<typename TNumber>
inline bool TVector3D<TNumber>::operator!=(TVector3D<TNumber> const & other)
{
	return !(this == other);
}

#endif // !VECTOR3D
