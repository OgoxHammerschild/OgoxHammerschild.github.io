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

        // The gameObject this component is attached to
        // (the parent)
	GameObject* gameObject;
	
        // The type of this component as a string
	string typeName;

public:
        // Constructors
	Component();
	virtual	~Component();

        // Gets the owning gameObject of this component
	GameObject* GetGameObject() const;

        // Sets the owning gameObject of this component while initialization
	void SetGameObject(GameObject* gameObject);

        // Removes the component from the owning gameObject and 
	// deletes the component
	virtual void Destroy();
};

#endif // !COMPONENT_H
