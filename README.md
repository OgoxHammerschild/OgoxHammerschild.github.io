# Daniel Bortfeld  

## Portfolio | Code Snippets | Unreal Examples  
***  

+ [Dynamic Delegate (C++)](#Collision_Manager)
+ [CollisionManager for the MonoGame-Framework (C#)](#Collision_Manager)
+ [Unreal Examples](https://ogoxhammerschild.github.io/Unreal-Examples/)   

<a name="Collision_Manager"/>

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

// Main.h

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

<a name="Collision_Manager"/>

<a name="Collision_Manager"/>

# Collision Manager for the MonoGame-Framework (C#)

I made a CollisionManager and a BoxCollider2D for my sidescroller in MonoGame. The CollisionManager checks all colliders against each other. The BoxCollider2D keeps the logic for checking whether he collides with a given collider.

```c#
// Copyright (c) 2016 Daniel Bortfeld
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;

namespace MyGame.Collision
{
    public static class CollisionManager
    {
        private static List<BoxCollider> colliders = new List<BoxCollider>();
        private static List<BoxCollider> removedColliders = new List<BoxCollider>();

        public static void AddCollider(BoxCollider collider)
        {
            colliders.Add(collider);
        }

        public static void Clear()
        {
            removedColliders.AddRange(colliders);
        }

        public static void RemoveCollider(BoxCollider collider)
        {
            removedColliders.Add(collider);
        }

        public static void UpdateColliders(GameTime gameTime)
        {
            colliders.ForEach(c => c.UpdatePosition(gameTime));
            CheckCollisions();

            removedColliders.ForEach(c => colliders.Remove(c));
            removedColliders.Clear();
        }

        private static void CheckCollisions()
        {
            foreach (var colliderA in colliders)
                foreach (var colliderB in colliders)
                    if (!colliderA.Equals(colliderB))
                        if (colliderA.IsActive && colliderB.IsActive)
                            colliderA.CheckCollision(colliderB);
        }
    }
}
```


# Simple Component System Example in C++

In a component system you have a container object and component objects which you can put into the container as a child. I call my container object GameObject.   
The GameObject keeps a list of its components and updates them when itself gets updated. In my case, a GameObject can possess every component only once.

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

	Hashtable components;

public:

	GameObject();
	
	GameObject(string name);

	virtual ~GameObject();

	template <typename T>
	bool HasComponent();

	template <typename T>
	std::shared_ptr<Component>& AddComponent();

	template <typename T>
	void RemoveComponent();

	//...

	template <typename T>
	std::shared_ptr<Component>& GetComponent();

	virtual void Destroy();

	//...
};

#endif // !GAME_OBJECT_H
```   

```c++
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
```
