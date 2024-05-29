// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObservationComponent.generated.h"

class AInterestPoint;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UObservationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UObservationComponent();

protected:
    virtual void BeginPlay() override;

    void GetInitialObservations(TArray<AInterestPoint*>& OutObservations) const;

protected:
    UPROPERTY()
    TArray<AInterestPoint*> CurrentObservations;
};