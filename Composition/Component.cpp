// (c) Daniel Bortfeld 2016 - 2017
#include "Component.h"
#include "GameObject.h"

Component::Component() : typeName("")
{
}

Component::~Component()
{
}

GameObject* Component::GetGameObject() const
{
	return gameObject;
}

void Component::SetGameObject(GameObject * gameObject)
{
	if (this->gameObject != nullptr)
	{
		printf_s("GameObject was already set for this component");
		return;
	}

	this->gameObject = gameObject;
}

void Component::Destroy()
{
	if (gameObject != nullptr)
	{
		if (typeName == "")
		{
			throw std::exception("Please specify the typeName of a derived component in its constructor");
		}
		gameObject->RemoveComponent(typeName);
	}
}
