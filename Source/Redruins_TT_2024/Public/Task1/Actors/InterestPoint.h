// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterestPoint.generated.h"

UCLASS()
class REDRUINS_TT_2024_API AInterestPoint : public AActor
{
    GENERATED_BODY()

public:
    AInterestPoint();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void Enable();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void Disable();

protected:
    virtual void BeginPlay() override;
};