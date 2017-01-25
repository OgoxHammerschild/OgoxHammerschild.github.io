# Daniel Bortfeld

## Portfolio | Code Snippets | Unreal Examples


# Unreal Examples


## Utility

First of all a little "trick" I use to highlight whether a paremeter is an *in*- or *out*-parameter and improve code readabilty.
*In*-parameter means that the variable used as a parameter will not be changed by the function.
*Out*-parameter means that the variable is used as a return value by the function and thus will be changed.

That's how:
```c++
// InOut.h

#ifndef INOUT_H
#define INOUT_H

#define in const&
#define out &

#endif ! INOUT_H
```
```c++
// other.h

#include "InOut.h"

//...
public:

// this
void GetDataByName(std::string in name, int out level, float out range);

// equals this
void GetDataByName(const std::string& name, int& level, float& range);
```

That's why:

When you 
By using the & operator on a parameter, the content of the variable will not be copied into the function but the reference of the variable itself will be used.
Thats why this will be the content of my *out* keyword.

Using the const keyword on a parameter will ensure that the variable can not be changed inside the function.

## UFUNCTION Specifiers

### BlueprintPure

Expose a single or multiple values from C++ to Blueprints

```c++
// .h

private:

UPROPERTY()
  float myRange;
  
public:

// specify a return value to return a single property
UFUNCTION(BlueprintPure, Category = "Range")
  float GetRange();  
  
// use &-parameters to return multiple properties
UFUNCTION(BlueprintPure, Category = "Data")
  void GetData(float& range, FString& name, int32& level);
```

Use **UPARAM** and the DisplayName specifier in case you have shortcuts or unclear names for your parameters

```c++
// .h

UFUNCTION(BlueprintPure, Category = "Data")
  void GetData(
    UPARAM(DisplayName = "Range") float& rng, 
    UPARAM(DisplayName = "Actor Name") FString& name, 
    UPARAM(DisplayName = "Level") int32& lvl);
```

### BlueprintNativeEvent vs BlueprintImplementableEvent

Use BlueprintNativeEvent if you want to include an optional native implementation for your exposed event

```c++
// .h

// I always use the prefix BPEvent_ to indicate that the body of the function will be defined within the Blueprint,
// but I don't want the prefix to show up inside the Blueprint. That's why I use the DisplayName meta-specifier

UFUNCTION(BlueprintImplementableEvent, Category = "Event")
  BPEvent_OnShoot(float range);
```
