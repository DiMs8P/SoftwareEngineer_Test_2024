// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointOfInterest.generated.h"

UENUM(BlueprintType)
enum class ViewMode : uint8
{
    Viewport,
    OutOfScreen
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScreenTargetVisibilityChanged, bool, bNewState);

UCLASS()
class REDRUINS_TT_2024_API UPointOfInterest : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetTargetLocation(const FVector& InTargetLocation);

    UFUNCTION(BlueprintCallable)
    void SetViewMode(const ViewMode InNewViewMode);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ShowMarker();
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    bool IsTargetOnPlayerScreen() const;

    UFUNCTION(BlueprintImplementableEvent)
    void K2_SetViewMode();

public:
    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnPlayerScreenTargetVisibilityChanged OnPlayerScreenTargetVisibilityChanged;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ViewMode TargetViewMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bVisibleOnPlayerScreen;
};
