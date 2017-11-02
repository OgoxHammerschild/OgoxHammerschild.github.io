# Daniel Bortfeld  

<a name="Etos_Video"/>   

## Portfolio | Code Snippets 
***    

# Etos   

Real-Time-Strategy City-Building Game in the style of the ANNO series

Build a strong economy with complex ware production chains and fulfil the challenging needs of your settlers to become the ultimate mayor.

<iframe width="640" height="360" src="https://www.youtube.com/embed/pd9AR2BzJ0E?rel=0" frameborder="0" allowfullscreen></iframe>   

***    
	
Further pages:    

+ [Etos Videos](https://ogoxhammerschild.github.io/Etos/)   
+ [Dynamic Delegate (C++)](#Dynamic_Delegate)
+ [CollisionManager for the MonoGame-Framework (C#)](https://ogoxhammerschild.github.io/Collision/)    
+ [Unreal Examples (C++)](https://ogoxhammerschild.github.io/Unreal-Examples/)   
+ [Pathfinding in the Console (C++)](https://ogoxhammerschild.github.io/Console-Pathfinding/)    

***   

<a name="Dynamic_Delegate"/>

# Dynamic Delegate (C++)

Define a **dynamic delegate** like in the Unreal framework, but without using the Unreal framework! The delegate can be subscribed by a pair of an Object\* and a function to call on the object. Broadcast() will call the functions on the respective objects.
**You will find the useage below and the source code in the [repository](https://github.com/OgoxHammerschild/OgoxHammerschild.github.io/blob/master/Composition/Delegate.h)**.

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

Further examples:   

* [Etos Videos](https://ogoxhammerschild.github.io/Etos/)    
* [Unreal Examples (C++)](https://ogoxhammerschild.github.io/Unreal-Examples/)   
* [CollisionManager for the MonoGame-Framework (C#)](https://ogoxhammerschild.github.io/Collision/)    
* [Pathfinding in the Console (C++)](https://ogoxhammerschild.github.io/Console-Pathfinding/)    

***    