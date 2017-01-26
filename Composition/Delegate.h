#ifndef DELEGATE_H
#define DELEGATE_H

#include "Object.h"
#include "Map.h"
#include <vector>
#include "GameObject.h"

#define IMPLEMENT_FUNCTION_PTR_RESOLVER_ReturnVal(ReturnValueType, /*FunctionParams*/ ...) \
template< class ObjectClass> \
class TFunctionPtrResolver \
{ \
public: \
 \
	typedef ReturnValueType(ObjectClass::*FunctionPtr)(__VA_ARGS__); \
}; \

#define IMPLEMENT_FUNCTION_PTR_RESOLVER(/*FunctionParams*/ ...) IMPLEMENT_FUNCTION_PTR_RESOLVER_ReturnVal(void, __VA_ARGS__)

#define DELEGATE_BASE_CLASS(Suffix, /*Params*/ ...) \
class DelegateBase##_##Suffix \
{ \
private: \
 \
	IMPLEMENT_FUNCTION_PTR_RESOLVER(__VA_ARGS__); \
 \
protected: \
 \
	typedef TMap<TFunctionPtrResolver<Object>::FunctionPtr, std::vector<Object*>> EventMap; \
\
	EventMap eventListener; \
 \
public: \
 \
	DelegateBase##_##Suffix() \
	{ \
		eventListener = EventMap(); \
	} \
 \
	~DelegateBase##_##Suffix() \
	{ \
		eventListener.Clear(); \
	} \
 \
	bool IsBound() \
	{ \
		return eventListener.Size() > 0; \
	} \
 \
	template <typename T> \
	void Add(T* object, typename TFunctionPtrResolver<T>::FunctionPtr function) \
	{ \
		if (object == nullptr || function == nullptr) \
			return; \
 \
		Object* Test = (T*)0; \
 \
		eventListener[(TFunctionPtrResolver<Object>::FunctionPtr)function].push_back(object); \
	} \
 \
	template <typename T> \
	bool Remove(T* object, typename TFunctionPtrResolver<T>::FunctionPtr function) \
	{ \
		if (object != nullptr && function != nullptr) \
		{ \
			for (auto& event : eventListener) \
			{ \
				if (function == event->Key) \
				{ \
					for (auto iter = event->Value.begin(); iter != event->Value.end(); ++iter) \
					{ \
						if (object == *iter) \
						{ \
							event->Value.erase(iter); \
							return true; \
						} \
					} \
				} \
			} \
		} \
		return false; \
	} \
 \
	template <typename T> \
	bool Remove(typename TFunctionPtrResolver<T>::FunctionPtr function) \
	{ \
		if (function != nullptr) \
		{ \
			for (auto iter = eventListener.begin(); iter != eventListener.end(); ++iter) \
			{ \
				if (function == iter->Key) \
				{ \
					eventListener.erase(iter); \
					return true; \
				} \
			} \
		} \
		return false; \
	} \
}; \

#define IMPLEMENT_BROADCAST_BODY(...) \
EventMap handler = eventListener; \
for (auto& function : handler) \
{ \
	for (int i = 0; i < function->Value.size(); ++i) \
	{ \
		if (function->Value[i] != nullptr) \
		{ \
			(function->Value[i]->*(function->Key))(__VA_ARGS__); \
		} \
	} \
} \

#define DELEGATE_SUB_CLASS(DelegateName, BroadcastBody, ...) \
class DelegateName : public DelegateBase##_##DelegateName \
{ \
public: \
 \
	void Broadcast(__VA_ARGS__) \
	{ \
		BroadcastBody \
	} \
}; \

#define DECLARE_DELEGATE(DelegateName) \
DELEGATE_BASE_CLASS(DelegateName, void) \
DELEGATE_SUB_CLASS(DelegateName, IMPLEMENT_BROADCAST_BODY(), )

#define DECLARE_DELEGATE_OneParam(DelegateName, ParamType1, ParamName1) \
DELEGATE_BASE_CLASS(DelegateName, ParamType1 ParamName1) \
DELEGATE_SUB_CLASS(DelegateName, IMPLEMENT_BROADCAST_BODY(ParamName1), ParamType1 ParamName1)

#define DECLARE_DELEGATE_TwoParams(DelegateName, ParamType1, ParamName1, ParamType2, ParamName2) \
DELEGATE_BASE_CLASS(DelegateName, ParamType1 ParamName1, ParamType2 ParamName2) \
DELEGATE_SUB_CLASS(DelegateName, IMPLEMENT_BROADCAST_BODY(ParamName1, ParamName2), ParamType1 ParamName1, ParamType2 ParamName2)

#define DECLARE_DELEGATE_ThreeParams(DelegateName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3) \
DELEGATE_BASE_CLASS(DelegateName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
DELEGATE_SUB_CLASS(DelegateName, IMPLEMENT_BROADCAST_BODY(ParamName1, ParamName2, ParamName3), ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3)

#endif // !DELEGATE
