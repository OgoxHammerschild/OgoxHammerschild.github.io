# Daniel Bortfeld
## Portfolio | Code Snippets | Unreal Examples #

# Unreal Example
## UFUNCTION Specifiers #

### BlueprintPure #

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

Use UPARAM and the DisplayName specifier in case you have shortcuts or unclear names for your parameters

```c++
// .h

UFUNCTION(BlueprintPure, Category = "Data")
  void GetData(
    UPARAM(DisplayName = "Range") float& rng, 
    UPARAM(DisplayName = "Actor Name") FString& name, 
    UPARAM(DisplayName = "Level") int32& lvl);
```
