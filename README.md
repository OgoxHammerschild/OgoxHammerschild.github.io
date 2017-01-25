# Daniel Bortfeld  

## Portfolio | Code Snippets | Unreal Examples  
***  

## Content

[Utility](#Utility)  
[Unreal Examples](#Unreal_Examples)  
[UFUNCTION Specifiers](#UFUNCTION_Specifiers)  

<a name="Utility"/>  

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

<a name="Unreal_Examples"/>  

# Unreal Examples    
***  

<a name="UFUNCTION_Specifiers"/>  

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
#include "InOut.h"

UFUNCTION(BlueprintPure, Category = "Data")
  void GetData(
    UPARAM(DisplayName = "Range") float out rng, 
    UPARAM(DisplayName = "Actor Name") FString out name, 
    UPARAM(DisplayName = "Level") int32 out lvl);
```

// TODO: picture

### BlueprintNativeEvent vs BlueprintImplementableEvent

Use BlueprintNativeEvent if you want to include an optional native implementation for your exposed event

```c++
// .h
#include "InOut.h"

// I always use the prefix BPEvent_ to indicate that the body of the function 
// will be defined within the Blueprint, but I don't want the prefix to show 
// up inside the Blueprint. That's why I use the DisplayName meta-specifier

// the body for this function will be declared inside the Blueprint Editor
UFUNCTION(BlueprintImplementableEvent, Category = "Event", meta = (DisplayName = "OnShoot"))
  void BPEvent_OnShoot(float in range);
  
// the native body for this function can(!) be called inside the Blueprint Editor
// otherwise it has no body like a BlueprintImplementableEvent
UFUNCTION(BlueprintNativeEvent, Category = "Event", meta = (DisplayName = "OnShoot"))
  void BPEvent_OnDestroy(AActor* destroyedActor);
  
// .cpp
  
  // for the declaration of your native body, add _Implementation to the function name
  void AMyClass::BPEvent_OnDestroy_Implementation(AActor* destroyedActor)
  {
    UE_LOG(LogTemp, Warning, TEXT("Call to native body of OnDestroy");
  }
```

// TODO: picture

### Expose multiple execution pins

The execution pins you see on a Branch node or a dynamic cast are based on enums. You can create your own functions with multiple execution pins on the output side

```c++
// .h
#include "InOut.h"

// First you need your enums
UENUM(BlueprintType)
enum class EBranch : uint8
{
  IsTrue,
  IsFalse
}

UENUM(BlueprintType)
enum class EHasItem : uint8
{
  Has,
  HasNot
}

UCLASS()
class AMyClass : public AActor
{
  // ...
  public:
  
  UPROPERTY()
    TArray<class AItem*> Inventory;
    
  public:
  
  // the meta specifier ExpandEnumAsExecs lets the execution pins show up in the Blueprint Editor
  UFUNCTION(BlueprintCallable, Category = FlowControl, meta = (Keyword = "if", ExpandEnumAsExecs="Branch"))
		  void MyOwnBranch(bool in condition, EBranch out Branch);
    
  UFUNCTION(BlueprintCallable, Category = Inventory, meta = (Keyword = "has", ExpandEnumAsExecs="Branch"))
		  bool DoesPlayerHaveItem(AItem* item, EHas out Has);
```

```c++
    // .cpp
  
    // to switch the branch, set the enum as the out-parameter's value
    void AMyClass::MyOwnBranch(bool in condition, EBranch out Branch)
    {
        condition ? Branch = EBranch::IsTrue : Branch = EBranch::IsFalse;
    }
   
    bool AMyClass::DoesPlayerHaveItem(AItem* item, EHas out Has)
    {
        for (auto& slot : Inventory)
        {
            if(slot == item)
            {
                Has = EHas::Has;
                return true;
            }
        }
        Has = EHas::HasNot;
        return false;
    }
}
```
