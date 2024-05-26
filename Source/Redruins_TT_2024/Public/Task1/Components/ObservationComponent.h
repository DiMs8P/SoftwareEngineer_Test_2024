// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObservationComponent.generated.h"


class IObservable;
class UPointOfInterest;



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UObservationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UObservationComponent();

protected:
    virtual void BeginPlay() override;

    void GetInitialObservations(TArray<TScriptInterface<IObservable>>& OutObservations) const;

protected:
    TMap<TScriptInterface<IObservable>, TObjectPtr<UPointOfInterest>> CurrentObservations;
	
protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UPointOfInterest> ObservationMarkerWidgetClass;
};