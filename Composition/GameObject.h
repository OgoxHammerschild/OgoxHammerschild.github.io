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

	Hashtable components;

public:

	GameObject();
	virtual ~GameObject();

	template <typename T>
	bool HasComponent();

	template <typename T>
	std::shared_ptr<Component>& AddComponent();

	template <typename T>
	void RemoveComponent();

	void RemoveComponent(type_info const& type);

	void RemoveComponent(string const& typeName);

	template <typename T>
	std::shared_ptr<Component>& GetComponent();

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
