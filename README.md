# Daniel Bortfeld  

## Portfolio | Code Snippets | Unreal Examples  
***  

## Utility  
First of all a little "trick" I use to highlight whether a paremeter is an *in*- or *out*-parameter and to improve code readabilty.  
By *in*-parameter I mean that the variable used as a parameter will not be changed by the function.  
By *out*-parameter I mean that the variable is used as a return value by the function and thus will be changed.  
  

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

# Unreal Examples  
***  

## UFUNCTION Specifiers

### BlueprintPure

Expose a single or multiple values from C++ to Blueprints

```c++
// .h
#include "InOut.h"

private:

UPROPERTY()
  float myRange;
  
public:

// specify a return value to return a single property
UFUNCTION(BlueprintPure, Category = "Range")
  float GetRange();  
  
// use &-parameters to return multiple properties
UFUNCTION(BlueprintPure, Category = "Data")
  void GetData(float out range, FString out name, int32 out level);
```

// TODO: picture

Use **UPARAM** and the DisplayName specifier in case you have shortcuts or unclear names for your parameters

```c++
// .h

UFUNCTION(BlueprintPure, Category = "Data")
  void GetData(
    UPARAM(DisplayName = "Range") float& rng, 
    UPARAM(DisplayName = "Actor Name") FString& name, 
    UPARAM(DisplayName = "Level") int32& lvl);
```

// TODO: picture

### BlueprintNativeEvent vs BlueprintImplementableEvent

Use BlueprintNativeEvent if you want to include an optional native implementation for your exposed event

```c++
// .h

// I always use the prefix BPEvent_ to indicate that the body of the function 
// will be defined within the Blueprint, but I don't want the prefix to show 
// up inside the Blueprint. That's why I use the DisplayName meta-specifier

// the body for this function will be declared inside the Blueprint Editor
UFUNCTION(BlueprintImplementableEvent, Category = "Event", meta = (DisplayName = "OnShoot"))
  void BPEvent_OnShoot(float range);
  
// the native body for this function can(!) be called inside the Blueprint Editor
// otherwise it has no body like a BlueprintImplementableEvent
UFUNCTION(BlueprintNativeEvent, Category = "Event", meta = (DisplayName = "OnShoot"))
  void BPEvent_OnDestroy(AActor* destroyedActor);
  
// .cpp
  
  // for the declaration of your native body, add _Implementation to the function name
  void MyClass::BPEvent_OnDestroy_Implementation(AActor* destroyedActor)
  {
    UE_LOG(LogTemp, Warning, TEXT("Call to native body of OnDestroy");
  }
```
