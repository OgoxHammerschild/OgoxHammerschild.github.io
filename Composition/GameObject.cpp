// (c) Daniel Bortfeld 2016 - 2017
#include "GameObject.h"
#include "Component.h"
#include <vector>

GameObject::GameObject() : components(Hashtable())
{
}

GameObject::~GameObject()
{
	std::vector<std::shared_ptr<Component>> temp;
	for (auto& i : components)
	{
		temp.push_back(i->Value);
	}
	for (auto& i : temp)
	{
		if (i.get() != nullptr)
		{
			i->Destroy();
		}
	}
}

void GameObject::RemoveComponent(type_info const& type)
{
	RemoveComponent(GetTypeName(type));
}

void GameObject::RemoveComponent(string const& typeName)
{
	if (components.Find(typeName) != nullptr)
	{
		components.Remove(typeName);
	}
}

void GameObject::Destroy()
{
	delete this;
}

string GameObject::GetTypeName(type_info const& type)
{
	string name = type.name();

	Replace(name, "class ", "");
	Replace(name, "*", "");
	Replace(name, " ", "");

	return name;
}

bool GameObject::Replace(string& yourString, string const& whatToReplace, string const& replaceWith)
{
	size_t start = yourString.find(whatToReplace);
	if (start == string::npos)
	{
		return false;
	}

	yourString.replace(start, whatToReplace.length(), replaceWith);
	return true;
}
