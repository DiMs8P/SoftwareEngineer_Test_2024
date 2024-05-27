// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveAlongSplineComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMoveAlongSplineComponent, All, All)

class UMovementComponent;
class USplineComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UMoveAlongSplineComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMoveAlongSplineComponent();
    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Start();

    UFUNCTION(BlueprintCallable)
    void AdjustSpeed(const float InSpeedAdjustment);

    UFUNCTION(BlueprintCallable)
    FVector GetCurrentVelocity();

protected:
    virtual void BeginPlay() override;

    void MoveAlongSpline(float DeltaTime);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* Spline;
    
    UPROPERTY(EditDefaultsOnly)
    float MinSpeed = 0;

    UPROPERTY(EditDefaultsOnly)
    float InitialSpeed = (MaxSpeed - MinSpeed) / 2;

    UPROPERTY(EditDefaultsOnly)
    float MaxSpeed = 15;

protected:
    UPROPERTY()
    TObjectPtr<USplineComponent> SplineComponent;
    
    float CurrentDistanceOnSpline = 0.0f;
    float CurrentSpeed = 0;

    FVector CurrentVelocity = FVector::Zero();

private:
    UPROPERTY()
    TObjectPtr<UMovementComponent> OwnerMovementComponent;
};