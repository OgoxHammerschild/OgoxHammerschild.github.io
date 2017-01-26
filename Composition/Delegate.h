#ifndef DELEGATE_H
#define DELEGATE_H

#include "Object.h"
#include "Map.h"
#include <vector>
#include "GameObject.h"

#define DECLARE_DELEGATE(DelegateName) 
#define DECLARE_DELEGATE_OneParams(DelegateName, ParamType1, ParamName1) 
#define DECLARE_DELEGATE_TwoParams(DelegateName, ParamType1, ParamName1, ParamType2, ParamName2) 
#define DECLARE_DELEGATE_ThreeParams(DelegateName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3)

#define IMPLEMENT_FUNCTION_PTR_RESOLVER_ReturnVal(ReturnValueType, /*FunctionParams*/ ...) \
	template< class ObjectClass> \
	class TFunctionPtrResolver \
	{ \
	public: \
	 \
		typedef ReturnValueType(ObjectClass::*FunctionPtr)(__VA_ARGS__); \
	}; \

#define IMPLEMENT_FUNCTION_PTR_RESOLVER(/*FunctionParams*/ ...) IMPLEMENT_FUNCTION_PTR_RESOLVER_ReturnVal(void, __VA_ARGS__)

class FunctionPointer;

//#define DELEGATE_BASE_CLASS(...)
class DelegateBase
{
private:
	
	IMPLEMENT_FUNCTION_PTR_RESOLVER(void);

private:

	//typedef TFunctionPtrResolver<Object>::FunctionPtr FunctionPointer;
	//typedef ReturnValue(*FunctionPointer)(ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3); 

protected:

	typedef std::vector<TPair<FunctionPointer, std::vector<Object*>>> EventMap;

	EventMap eventListener;

public:

	DelegateBase()
	{
		eventListener = EventMap();
	}

	~DelegateBase()
	{
		eventListener.clear();
	}

	void Broadcast()
	{
		EventMap handler = eventListener;
		for (auto& function : handler)
		{
			for (int i = 0; i < function.Value.size(); ++i)
			{
				if (function.Value[i] != nullptr)
				{
					(function.Value[i]->*(function.Key))();
				}
			}
		}
	}

	bool IsBound()
	{
		return eventListener.size() > 0;
	}

	template <typename T>
	void Add(T* object, typename TFunctionPtrResolver<T>::FunctionPtr function)
	{
		if (object == nullptr || function == nullptr)
			return;

		Object* Test = (T*)0; // does T derive from Object?

		eventListener.push_back(TPair<T*, TFunctionPtrResolver<T>::FunctionPtr>(object, function));
	}

	// Remove a function or a specific object from the caller list
	// @object: the object that calls the function
	// @function: the function to remove a caller from
	template <typename T>
	bool Remove(T* object, TFunctionPtrResolver<T>::FunctionPtr function)
	{
		if (object != nullptr && function != nullptr)
		{
			for (auto& event : eventListener)
			{
				if (function == event.Key)
				{
					for (auto iter = event.Value.begin(); iter != event.Value.end(); ++iter)
					{
						if (object == *iter)
						{
							event.Value.erase(iter);
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	template <typename T>
	bool Remove(TFunctionPtrResolver<T>::FunctionPtr function)
	{
		if (function != nullptr)
		{
			for (auto iter = eventListener.begin(); iter != eventListener.end(); ++iter)
			{
				if (function == iter->Key)
				{
					eventListener.erase(iter);
					return true;
				}
			}
		}
		return false;
	}
}; \

class MyClass : public DelegateBase
{
private:

	IMPLEMENT_FUNCTION_PTR_RESOLVER(int);
	typedef TFunctionPtrResolver<Object>::FunctionPtr FunctionPointer;

public:

	void Broadcast()
	{
		EventMap handler = eventListener;
		for (auto& function : handler)
		{
			for (int i = 0; i < function.Value.size(); ++i)
			{
				if (function.Value[i] != nullptr)
				{
					(function.Value[i]->*(function.Key))();
				}
			}
		}
	}


	MyClass();
	~MyClass();

private:

};

#endif // !DELEGATE
