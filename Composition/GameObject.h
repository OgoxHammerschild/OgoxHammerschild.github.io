// (c) Daniel Bortfeld 2016 - 2017
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class Component;

#include "Object.h"
#include "Map.h"
#include <memory>
#include <string>
using std::string;

class GameObject : public Object
{
public:

	string Name = "Unnamed GameObject";

	string Tag = "None";

protected:

	typedef TMap<string, std::shared_ptr<Component>> Hashtable;
	
	// The components of this gameObject
	Hashtable components;

public:
	// Constructors
	GameObject();
	
	GameObject(string name);

	virtual ~GameObject();
	
	// Whether this gameObject possesses the specified component
	// @T = the type of the component
	template <typename T>
	bool HasComponent();
	
	// Adds a component to this gameObject
	// @T = the type of the component
	// returns the newly added component
	template <typename T>
	std::shared_ptr<Component>& AddComponent();

	// Removes a component from this gameObject
	// @T = the type of the component
	template <typename T>
	void RemoveComponent();
	
	// Removes a component from this gameObject
	// @type = typeid(T) where T is the type of the component
	void RemoveComponent(type_info const& type);
	
	// Removes a component from this gameObject
	// @typeName = the type of the component as string
	void RemoveComponent(string const& typeName);

	// Gets the specified component from this gameObject
	// if the gameObject contains the component
	// @T = the type of the component
	template <typename T>
	std::shared_ptr<Component>& GetComponent();

	// Deletes this gameObject 
	virtual void Destroy();

private:

	template <typename T>
	string GetTypeName();

	string GetTypeName(type_info const& type);

	bool Replace(string& yourString, string const& whatToReplace, string const& replaceWith);
};

template<typename T>
inline bool GameObject::HasComponent()
{
	return components.Find(GetTypeName<T>()) != nullptr;
}

template<typename T>
inline std::shared_ptr<Component>& GameObject::AddComponent()
{
	if (std::is_base_of<Component, T>::value)
	{
		if (!HasComponent<T>())
		{
			std::shared_ptr<T> component(new T());
			component->SetGameObject(this);
			components.Add(GetTypeName<T>(), component);
			// start component
		}
	}
	return this->GetComponent<T>();
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	if (HasComponent<T>())
	{
		//std::shared_ptr<Component>* component = components.Find(GetTypeName<T>());
		//component->reset();
		components.Remove(GetTypeName<T>());
	}
}

template<typename T>
inline std::shared_ptr<Component>& GameObject::GetComponent()
{
	//Component* tempComponent = components[typeid(T).name()].get();
	//T* component = dynamic_cast<T*>(tempComponent);
	//return std::shared_ptr<T>(component);

	return components[GetTypeName<T>()];
}

template<typename T>
inline std::string GameObject::GetTypeName()
{
	return GetTypeName(typeid(T));
}

#endif // !GAME_OBJECT_H
