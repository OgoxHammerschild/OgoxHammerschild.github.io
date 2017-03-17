# Daniel Bortfeld  

## Portfolio | Code Snippets | Unreal Examples  
***  


# Content

On this page:    

+ [Dynamic Delegate (C++)](#Dynamic_Delegate)
+ [Component System (C++)](#Component_System)
	+ [GameObject](#GameObject)
	+ [Component](#Component)
	+ [Functionality Test](#Test)
	
Further pages:    

+ [CollisionManager for the MonoGame-Framework (C#)](https://ogoxhammerschild.github.io/Collision/)    
+ [Unreal Examples (C++)](https://ogoxhammerschild.github.io/Unreal-Examples/)   
+ [Pathfinding in the Console (C++)](https://ogoxhammerschild.github.io/Console-Pathfinding/)    

***   

<a name="Dynamic_Delegate"/>

# Dynamic Delegate (C++)

Define a **dynamic delegate** like in the Unreal framework, but without using the Unreal framework! The delegate can be subscribed by a pair of an Object\* and a function to call on the object. Broadcast() will call the functions on the respective objects.
You will find the useage below and the source code in the [repository](https://github.com/OgoxHammerschild/OgoxHammerschild.github.io/blob/master/Composition/Delegate.h).

```c++
// (c) Daniel Bortfeld 2016 - 2017

// GameObject.cpp

void GameObject::Destroy()
{
	std::cout << Name << " was destroyed" << std::endl;
	delete this;
}

// Main.cpp

#include "Delegate.h"

DECLARE_DELEGATE(DestroyDelegate)

int main()
{
	DestroyDelegate Destroy;
    
	GameObject* gameObject2 = new GameObject("GO 1");
	GameObject* gameObject3 = new GameObject("GO 2");
	GameObject* gameObject4 = new GameObject("GO 3");
    
    printf_s("Adding function GameObject::Destroy of GO 1, 2 & 3 to delegate Destroy...\n");
	Destroy.Add<GameObject>(gameObject2, &GameObject::Destroy);
	Destroy.Add<GameObject>(gameObject3, &GameObject::Destroy);
	Destroy.Add<GameObject>(gameObject4, &GameObject::Destroy);
    
    // ...
    
    printf_s("Broadcasting delegate Destroy...\n");
	Destroy.Broadcast();
    
    return 0;
```

### Output

Adding function GameObject::Destroy of GO 1, 2 & 3 to delegate Destroy...    
Broadcasting delegate Destroy...    
GO 1 was destroyed    
GO 2 was destroyed    
GO 3 was destroyed    

***   

<a name="Component_System"/>

# Simple Component System Example in C++

<a name="GameObject"/>

## GameObject

In a component system you have a container object and component objects which you can put into the container as a child. I call my container object GameObject.   
The GameObject keeps a list of its components and  - in my case - can possess every component only once.   
It also serves as a base class for derived gameObjects.

```c++
// (c) Daniel Bortfeld 2016 - 2017
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// ... includes ...

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

        //...

        // Gets the specified component from this gameObject
        // if the gameObject contains the component
        // @T = the type of the component
	template <typename T>
	std::shared_ptr<Component>& GetComponent();

        // Deletes this gameObject 
	virtual void Destroy();

	//...
};

#endif // !GAME_OBJECT_H
```   

***   

<a name="Component"/>

## Component

The component contains a specific set of logic. The logic of a GameObject is formed from the logic of its components.
As an example, a component can be a Transform, a SpriteRenderer, a Health-Component or an AI-Component.

```c++
// (c) Daniel Bortfeld 2016 - 2017
#ifndef COMPONENT_H
#define COMPONENT_H

// ... includes ...

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
```

***   

<a name="Test"/>

## Functionality Test

This program will test if the functions of the Component System will work.

```c++
// (c) Daniel Bortfeld 2016 - 2017

// ... inlcudes ...

int main()
{
	std::shared_ptr<GameObject> gameObject(new GameObject());

	printf_s("Adding Transform to GameObject ...\n");
	gameObject->AddComponent<Transform>();

	if (gameObject->HasComponent<Transform>())
	{
		printf_s("GameObject has transform\n");
	}

	printf_s("Removing Transform from GameObject ...\n");
	gameObject->RemoveComponent<Transform>();

	if (!gameObject->HasComponent<Transform>())
	{
		printf_s("GameObject has no transform\n");
	}

	gameObject->AddComponent<Transform>();

	gameObject.reset();

	return 0;
}
```

### Output

Adding Transform to GameObject ...    
GameObject has transform    
Removing Transform from GameObject ...    
GameObject has no transform     

***    

Further examples:   

+ [Unreal Examples (C++)](https://ogoxhammerschild.github.io/Unreal-Examples/)   
+ [CollisionManager for the MonoGame-Framework (C#)](https://ogoxhammerschild.github.io/Collision/)    
+ [Pathfinding in the Console (C++)](https://ogoxhammerschild.github.io/Console-Pathfinding/)    

***    
