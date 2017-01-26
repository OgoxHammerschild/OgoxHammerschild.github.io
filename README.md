# Daniel Bortfeld  

## Portfolio | Code Snippets | Unreal Examples  
***  

+ [Unreal Examples](https://ogoxhammerschild.github.io/Unreal-Examples/)   

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

In a component system you have a container object and component objects which you can put into the container. I call my container object GameObject.   
The GameObject keeps a list of its components and updates them when itself gets updated. In my case, every component can 
