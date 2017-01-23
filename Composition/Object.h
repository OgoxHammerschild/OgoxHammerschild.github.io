#ifndef OBJECT_H
#define OBJECT_H

class Object
{

#define SUPER Object

public:

	Object() {}
	virtual ~Object() {}

	virtual void Destroy() = 0;
};

#endif // !OBJECT_H
