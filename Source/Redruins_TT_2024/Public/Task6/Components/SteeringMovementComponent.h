// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SteeringMovementComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSteeringMovementComponent, All, All)

class IObservable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API USteeringMovementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USteeringMovementComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void SetObservation(AActor* InTarget);

    UFUNCTION(BlueprintCallable)
    void Start();

protected:
    virtual void BeginPlay() override;

    void HandleCollision(const FHitResult& InHitResult);

private:
    FVector GetTargetAcceleration() const;
    FVector GetDynamicObjectsAcceleration() const;

    void UpdateAcceleration();
    void UpdateVelocity(float DeltaTime);

    FRotator GetRotatorFromDeltaLocation(const FVector& InDeltaLocation) const;
    FVector GetInitialMovementDirection() const;
    
    void DebugDraw(float DeltaTime);
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TEnumAsByte<EAxis::Type> ForwardAxis = EAxis::Type::X;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ToolTip = "Initial speed"))
    float InitialSpeed = 200;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ToolTip = "Shows how much the target's gravity affects movement"))
    float TargetAccelerationFactor = 200.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ToolTip = "Shows how much the dynamic objects's gravity affects movement"))
    float DynamicObjectsAccelerationFactor = 50.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ToolTip = "Shows how strongly an object will be repelled upon collision"))
    float CollisionImpactFactor = 10000.f;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
    bool bDebugEnable = true;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
    float DebugLineLength = 100;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
    float DebugEverySeconds = 0.0f;
    
protected:
    UPROPERTY()
    AActor* Target;

    UPROPERTY()
    TArray<AActor*> DynamicObjects;

    FVector CurrentVelocity = FVector::Zero();
    FVector CurrentAcceleration = FVector::Zero();

private:
    float CurrentDebugTime = 0.0f;
};