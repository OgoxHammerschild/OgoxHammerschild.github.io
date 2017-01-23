// (c) Daniel Bortfeld 2016 - 2017
#ifndef TRANSFORM_H
#define	TRANSFORM_H

#include "Component.h"
#include "Vector3D.h"

class Transform : public Component
{
public:

	Vector3D Position;
	//Vector3D Position;
	Vector3D Scale;

public:

	Transform();
	virtual ~Transform();

	void Translate(float X, float Y, float Z);
	void Translate(Vector3D const& translation);


};

#endif // !TRANSFORM_H
