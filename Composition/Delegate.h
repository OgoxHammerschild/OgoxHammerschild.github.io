#ifndef DELEGATE_H
#define DELEGATE_H

#include "Object.h"
#include "Map.h"
#include <vector>
#include "GameObject.h"

#define DECLARE_DELEGATE_ThreeParams_WithReturnValue(DelegateName, ReturnValue, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3) \


class DelegateName
{
private:

	typedef void(Object::*FunctionPointer)();
	//typedef ReturnValue(*FunctionPointer)(ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3); 
	typedef std::vector<TPair<Object*, FunctionPointer>> SubscriberList;

	SubscriberList subscribers;

public:

	DelegateName()
	{
		subscribers = SubscriberList();
	}

	~DelegateName()
	{
		subscribers.clear();
	}

	void Broadcast()
	{
		SubscriberList handler = subscribers;
		for (int i = 0; i < handler.size(); ++i)
		{
			(handler[i].Key->*handler[i].Value)();
		}
	}

	bool IsBound()
	{
		return subscribers.size() > 0;
	}

	template <typename T>
	void Add(Object* object, void(T::*pointer)())
	{
		Object* Test = (T*)0; // does T derive from Object?

		Object* asdf = (DelegateName*)0;

		subscribers.push_back(TPair<Object*, FunctionPointer>(object, pointer));
	}

	void Remove(Object* object, FunctionPointer pointer)
	{
		for (auto iter = subscribers.begin(); iter != subscribers.end(); ++iter)
		{
			if (object == iter->Key && pointer == iter->Value)
			{
				subscribers.erase(iter);
				return;
			}
		}
	}

	void RemoveAll(Object* object, FunctionPointer pointer)
	{
		for (auto iter = subscribers.begin(); iter != subscribers.end(); ++iter)
		{
			if (object == iter->Key && pointer == iter->Value)
			{
				subscribers.erase(iter);
			}
		}
	}
}; \

#endif // !DELEGATE
