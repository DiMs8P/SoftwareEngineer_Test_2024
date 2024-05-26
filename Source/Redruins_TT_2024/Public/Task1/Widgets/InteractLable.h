// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractLable.generated.h"

class IInteractable;
/**
 * 
 */
UCLASS()
class REDRUINS_TT_2024_API UInteractLable : public UUserWidget
{
    GENERATED_BODY()

public:
    void ShowLable(AActor* NewInteraction);
    void HideLable();

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void K2_ShowLable();

    UFUNCTION(BlueprintImplementableEvent)
    void K2_HideLable();

protected:
    UPROPERTY(BlueprintReadWrite)
    AActor* Interaction;
};
