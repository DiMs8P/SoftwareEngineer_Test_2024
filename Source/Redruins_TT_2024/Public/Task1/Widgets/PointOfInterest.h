// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointOfInterest.generated.h"

class IObservable;
/**
 * 
 */
UCLASS()
class REDRUINS_TT_2024_API UPointOfInterest : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetObservation(TScriptInterface<IObservable> NewObservation);

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void  K2_SetObservation();
    
protected:
    UPROPERTY(BlueprintReadWrite)
    TScriptInterface<IObservable> Observation;
};
