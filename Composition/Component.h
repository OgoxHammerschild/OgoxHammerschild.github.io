// (c) Daniel Bortfeld 2016 - 2017
#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

#include "Object.h"
#include <memory>
#include <string>
using std::string;

class Component : public Object
{
protected:

	GameObject* gameObject;
	string typeName;

public:

	Component();
	virtual	~Component();

	GameObject* GetGameObject() const;

	void SetGameObject(GameObject* gameObject);

	virtual void Destroy();
};

#endif // !COMPONENT_H
