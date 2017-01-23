#include "Vector2D.h"

template<typename TNumber>
TVector2D<TNumber>::TVector2D()
{
}

template<typename TNumber>
TVector2D<TNumber>::TVector2D(TNumber X, TNumber Y)
{
	this->X = X;
	this->Y = Y;
}

template<typename TNumber>
TVector2D<TNumber>::~TVector2D()
{
}

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
