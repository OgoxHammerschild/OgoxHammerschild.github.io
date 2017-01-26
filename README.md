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

// ... includes ...

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


# Collision Manager for the MonoGame-Framework (C#)

I made a CollisionManager and a BoxCollider2D for my sidescroller in MonoGame. The CollisionManager checks all colliders against each other. The BoxCollider2D keeps the logic for checking whether he collides with a given collider.

```c#
// Copyright (c) 2016 Daniel Bortfeld
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;

namespace MonoGamePortal3Practise
{
    public static class CollisionManager
    {
        private static List<BoxCollider> colliders = new List<BoxCollider>();
        private static List<BoxCollider> removedColliders = new List<BoxCollider>();

        /// <summary>
        /// Register a collider for collision checks in the Manager.
        /// </summary>
        /// <param name="collider">The collider to add.</param>
        public static void AddCollider(BoxCollider collider)
        {
            colliders.Add(collider);
        }

        /// <summary>
        /// Remove all registered Colliders from the Manager's collision check  list.
        /// </summary>
        public static void Clear()
        {
            removedColliders.AddRange(colliders);
        }

        /// <summary>
        /// Remove a specific collider from being checked for collisions by the Manager.
        /// </summary>
        /// <param name="collider">The collider to remove.</param>
        public static void RemoveCollider(BoxCollider collider)
        {
            removedColliders.Add(collider);
        }

        /// <summary>
        /// Update function of the Manager. Call this every frame.
        /// </summary>
        /// <param name="gameTime">delta time</param>
        public static void UpdateColliders(GameTime gameTime)
        {
            colliders.ForEach(c => c.UpdatePosition(gameTime));
            CheckCollisions();

            removedColliders.ForEach(c => colliders.Remove(c));
            removedColliders.Clear();
        }

        /// <summary>
        /// Checks all registered colliders against each other
        /// </summary>
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

## Box Collider 2D for the MonoGame-Framework (C#)

```c#
// Copyright (c) 2016 Daniel Bortfeld
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;

namespace MonoGamePortal3Practise
{
    public class BoxCollider
    {
        public delegate void CollisionEvent(BoxCollider other);
        public event CollisionEvent OnCollisionEnter, OnCollisionStay, OnCollisionExit;

	//...

        // rectangle:
        public int X;
        public int Y;
        public int Width;
        public int Height;

        /// <summary>
        /// Current collisions of this collider
        /// </summary>
        private List<BoxCollider> collisions = new List<BoxCollider>();

        // rect sides
        public int Top { get { return Y; } }
        public int Bottom { get { return Y + Height; } }
        public int Left { get { return X; } }
        public int Right { get { return X + Width; } }

        /// <summary>
        /// The center point of the collider rect
        /// </summary>
        public Vector2 Center
        {
            get { return new Vector2(X, Y) + new Vector2(Width / 2, Height / 2); }
            set { X = (int)value.X - Width / 2; Y = (int)value.Y - Height / 2; }
        }

        /// <summary>
        /// The GameObject the BoxCollider is attached to
        /// </summary>
        public GameObject GameObject { get; private set; }

        // Constructor
        public BoxCollider(GameObject gameObject, int width, int height, bool isTrigger)
        {
            GameObject = gameObject;
            X = (int)GameObject.Position.X;
            Y = (int)GameObject.Position.Y;
            Width = width;
            Height = height;
            IsTrigger = isTrigger;

            CollisionManager.AddCollider(this);
        }

	// ...

        /// <summary>
        /// Checks whether this collider collides with the other collider. Calls respecive collision events.
        /// </summary>
        /// <param name="other"></param>
        public void CheckCollision(BoxCollider other)
        {
            if (!isActive || !other.isActive ||
                Right < other.Left || other.Right < Left || Bottom < other.Top || other.Bottom < Top)
            {
                // no collision
                if (collisions.Contains(other))
                {
                    // no more colliding
                    if (OnCollisionExit != null)
                        OnCollisionExit(other);
                    collisions.Remove(other);
                }
                return;
            }

            if (collisions.Contains(other))
            {
                // still colliding
                if (OnCollisionStay != null)
                    OnCollisionStay(other);
                return;
            }

            // new collison
            collisions.Add(other);
            if (OnCollisionEnter != null)
                OnCollisionEnter(other);
        }

        // ...

        #region Minkowsky sum (Magic)

        /// <summary>
        /// Whether this collider is colliding with the top of the other
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public bool CollidesWithTopOf(BoxCollider other)
        {
            float wy = (Width + other.Width) * (Center.Y - other.Center.Y);
            float hx = (Height + other.Height) * (Center.X - other.Center.X);

            if (wy <= -hx && wy <= hx)
                return true;
            return false;
        }

        /// <summary>
        /// Whether this collider is colliding with the bottom of the other
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public bool CollidesWithBottomOf(BoxCollider other)
        {
            float wy = (Width + other.Width) * (Center.Y - other.Center.Y);
            float hx = (Height + other.Height) * (Center.X - other.Center.X);

            if (wy > -hx && wy > hx)
                return true;
            return false;
        }

	// ...

        #endregion Minkowsky sum (Magic)

        /// <summary>
        /// Remove this collider from the collider manager.
        /// </summary>
        public void Remove()
        {
            CollisionManager.RemoveCollider(this);
        }
    }
}
```
