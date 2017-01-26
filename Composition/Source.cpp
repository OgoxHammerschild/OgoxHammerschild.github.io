// (c) Daniel Bortfeld 2016 - 2017

#include "Delegate.h"
#include "GameObject.h"
#include "Transform.h"
#include <string>
#include <iostream>
#include <memory>
using std::string;

DECLARE_DELEGATE(DestroyDelegate)

int main()
{
	DestroyDelegate Destroy;

	std::shared_ptr<GameObject> gameObject(new GameObject());

	GameObject* gameObject2 = new GameObject("GO 1");
	GameObject* gameObject3 = new GameObject("GO 2");
	GameObject* gameObject4 = new GameObject("GO 3");

	printf_s("Adding function GameObject::Destroy of GO 1, 2 & 3 to delegate Destroy...\n");
	Destroy.Add<GameObject>(gameObject2, &GameObject::Destroy);
	Destroy.Add<GameObject>(gameObject3, &GameObject::Destroy);
	Destroy.Add<GameObject>(gameObject4, &GameObject::Destroy);

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

	printf_s("Broadcasting delegate Destroy...\n");
	Destroy.Broadcast();

	return 0;
}