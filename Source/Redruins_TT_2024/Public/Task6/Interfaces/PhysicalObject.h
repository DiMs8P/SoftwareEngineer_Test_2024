// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PhysicalObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPhysicalObject : public UInterface
{
    GENERATED_BODY()
};

/**
 * 
 */
class REDRUINS_TT_2024_API IPhysicalObject
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintImplementableEvent)
    float GetAccelerationFactor() const;
};