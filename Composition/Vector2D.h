// (c) Daniel Bortfeld 2016 - 2017
#ifndef VECTOR2D
#define VECTOR2D

#include <math.h>

template <typename TNumber>
class TVector2D
{
public:

	TNumber X = 0;
	TNumber Y = 0;

public:

	TVector2D() {}

	TVector2D(TVector2D<int> const& other) : X(other.X), Y(other.Y) {}
	TVector2D(TVector2D<float> const& other) : X(other.X), Y(other.Y) {}

	TVector2D(TNumber const& X, TNumber const& Y) : X(X), Y(Y) {}

	// Returns a Vector with X and Y being 0
	static TVector2D<TNumber>& Zero();

	// Returns the Euler Angle between the specified Vectors
	static float GetAngle(TVector2D<TNumber> const& A, TVector2D<TNumber> const& B);

	// Returns the Distance between the specified Vectors
	static float GetDistance(TVector2D<TNumber> const& A, TVector2D<TNumber> const& B);

	// Returns the Dot-Product between the specified Vectors
	static float GetDotProduct(TVector2D<TNumber> const& A, TVector2D<TNumber> const& B);

	// Returns a normalized version of the Vector without changing it directly
	TVector2D<TNumber>& GetNormalized() const;

	// Normalizes the Vector
	void Normalize();

	// Returns the magnitude of the Vector (same as length)
	float& GetMagnitude() const;

	// Returns the length of the Vector (same as magnitude)
	float& GetLength() const;

	// Returns the reversed version of the Vector without changing it directly
	TVector2D<TNumber>& GetReversed() const;

	// Reverses the Vector
	void Reverse();

	// Reverses the Vector
	TVector2D<TNumber>& operator-() const;

	TVector2D<TNumber>& operator+(TVector2D<TNumber> other) const;
	TVector2D<TNumber>& operator-(TVector2D<TNumber> const& other) const;
	TVector2D<TNumber>& operator*(TNumber const& scalar) const;
	TVector2D<TNumber>& operator/(TNumber const& scalar) const;

	// Returns the Dot-Product of the Vectors
	float& operator*(TVector2D<TNumber> const& other) const;

	TVector2D<TNumber>& operator+=(TVector2D<TNumber> const& other);
	TVector2D<TNumber>& operator-=(TVector2D<TNumber> const& other);
	TVector2D<TNumber>& operator*=(TNumber const& scalar);
	TVector2D<TNumber>& operator/=(TNumber const& scalar);

	// Checks components of the vector for equality
	bool operator==(TVector2D<TNumber> const& other);
	// Checks components of the vector for inequality
	bool operator!=(TVector2D<TNumber> const& other);
};

typedef TVector2D<float> Vector2D;
typedef TVector2D<int> Vector2Di;

template<typename TNumber>
TVector2D<TNumber>& TVector2D<TNumber>::Zero()
{
	return TVector2D<TNumber>(0, 0);
}

template<typename TNumber>
float TVector2D<TNumber>::GetAngle(TVector2D<TNumber> const & A, TVector2D<TNumber> const & B)
{
	return std::acos((A*B) / (A.GetMagnitude()*B.GetMagnitude()));
}

template<typename TNumber>
float TVector2D<TNumber>::GetDistance(TVector2D<TNumber> const & A, TVector2D<TNumber> const & B)
{
	return (B - A).GetLength();
}

template<typename TNumber>
float TVector2D<TNumber>::GetDotProduct(TVector2D<TNumber> const & A, TVector2D<TNumber> const & B)
{
	return A * B;
}

template<typename TNumber>
TVector2D<TNumber>& TVector2D<TNumber>::GetNormalized() const
{
	return this / GetMagnitude();
}

template<typename TNumber>
void TVector2D<TNumber>::Normalize()
{
	this /= GetMagnitude();
}

template<typename TNumber>
inline float& TVector2D<TNumber>::GetMagnitude() const
{
	return std::sqrt(X*X + Y*Y);
}

template<typename TNumber>
inline float& TVector2D<TNumber>::GetLength() const
{
	return GetMagnitude();
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::GetReversed() const
{
	return TVector2D<TNumber>(-X, -Y);
}

template<typename TNumber>
inline void TVector2D<TNumber>::Reverse()
{
	X = -X;
	Y = -Y;
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator+(TVector2D<TNumber> other) const
{
	return TVector2D<TNumber>(X + other.X, Y + other.Y);
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator-(TVector2D<TNumber> const & other) const
{
	return TVector2D<TNumber>(X - other.X, Y - other.Y);
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator*(TNumber const & scalar) const
{
	return TVector2D<TNumber>(X * scalar, Y * scalar);
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator/(TNumber const & scalar) const
{
	return TVector2D<TNumber>(X / scalar, Y / scalar);
}

template<typename TNumber>
inline float & TVector2D<TNumber>::operator*(TVector2D<TNumber> const & other) const
{
	return X * other.X + Y * other.Y;
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator-() const
{
	return GetReversed();
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator+=(TVector2D<TNumber> const & other)
{
	this = this + other;
	return *this;
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator-=(TVector2D<TNumber> const & other)
{
	this = this - other;
	return *this;
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator*=(TNumber const & scalar)
{
	this = this * scalar;
	return *this;
}

template<typename TNumber>
inline TVector2D<TNumber>& TVector2D<TNumber>::operator/=(TNumber const & scalar)
{
	this = this / scalar;
	return *this;
}

template<typename TNumber>
inline bool TVector2D<TNumber>::operator==(TVector2D<TNumber> const & other)
{
	return (X == other.X && Y == other.Y);
}

template<typename TNumber>
inline bool TVector2D<TNumber>::operator!=(TVector2D<TNumber> const & other)
{
	return !(this == other);
}

#endif // !VECTOR2D
