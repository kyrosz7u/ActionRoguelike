# The Interface with UE Reflection System

## Problem Background
In my ActionRougelike Game Development, many actors could be interacted with character, such as chest, switch, door, etc. The character could interact with them by pressing the interact key. The interact key is the same for all the interactable actors. So I need to implement an interface for all the interactable actors. The interface will provide a function for the character to interact with the different interactable actors.

## Implement the Interface in native C++
### Create the Interface
```c++
// IAGameplayInterface.h
class ACTIONROGUELIKE_API IAGameplayInterface
{
public:
	virtual void Interact(APawn* InstigatorPawn) = 0;
};
```
It is same as other c++ code, interface is just a class with pure virtual function. The interface is a abstract class, so it can not be instantiated. The subclass which implement the interface must implement all the pure virtual functions in the interface.
### Implement the Interface
```c++
// AItemChest.h
class ACTIONROGUELIKE_API AAItemChest : public AActor, public IAGameplayInterface
{
public:
    virtual void Interact(APawn* InstigatorPawn) override;
};

// AItemChest.cpp
void AAItemChest::Interact(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(LidOpenAngle, 0.0f, 0.0f));
}
```
The subclass AAItemChest implement the pure virtual functions Interact in the interface. So Its Interact function can be called through the interface pointer.
### Use the Interface
```c++
// AItemInteractionComponent.cpp
void UAItemInteractionComponent::Interact()
{
    GetWorld()->LineTraceSingleByObjectType(hit, s, e, params);
    AActor* a = hit.GetActor();
    if(a != nullptr)
    {
        // Actor* -> Chest* -> IAGameplayInterface*, if the subclass of Actor not implement the interface, the dynamic_cast will return nullptr
        auto i = dynamic_cast<IAGameplayInterface*>(a);
        if(i != nullptr)
        {
            i->Interact(Cast<APawn>(o));
        }
    }
}
```
The character interact with the interactable actors by calling the Interact function in its ItemInteractionComponent. When player press the interact key, the ItemInteractionComponent will do a line trace to find the interactable actor. If the actor implement the interface, the ItemInteractionComponent will call the Interact function in the interface. The character will interact with the actor through the interface.

How to determine whether the actor implement the interface? When the actor is a subclass of both Actor and IAGameplayInterface, the actor implement the interface. So we can use dynamic_cast to determine whether the actor implement the interface. If the actor implement the interface, the dynamic_cast will return a pointer to the interface. Otherwise, the dynamic_cast will return nullptr.
### Enable C++ RTTI Build
```csharp
// ActionRougelike.Build.cs
public ActionRoguelike(ReadOnlyTargetRules Target) : base(Target)
{
    bUseRTTI = true;
}
```
The dynamic_cast need RTTI support. So we need to enable RTTI in the build.cs file. UE4 disable RTTI by default because it will increase the binary size and 
lead to some compatibility issues.

Although, we have implemented the interface in native C++. But the interface is not a native UE4 interface. We can not use the interface in UE4 reflection system and Blueprints. So we need to implement the interface in UE4 reflection system.
## Implement the Interface with UE's Reflection System


