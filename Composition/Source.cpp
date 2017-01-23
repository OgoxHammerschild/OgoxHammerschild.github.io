// (c) Daniel Bortfeld 2016 - 2017
#include "GameObject.h"
#include "Transform.h"
#include <string>
#include <iostream>
#include <memory>
using std::string;

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