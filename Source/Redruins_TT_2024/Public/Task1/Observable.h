// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Observable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UObservable : public UInterface
{
    GENERATED_BODY()
};

/**
 * 
 */
class REDRUINS_TT_2024_API IObservable
{
    GENERATED_BODY()

public:
    // The purpose is to divide Interactable objects and Observable because not every Interactable object should be observed
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FVector GetObservationLocation() const;
};