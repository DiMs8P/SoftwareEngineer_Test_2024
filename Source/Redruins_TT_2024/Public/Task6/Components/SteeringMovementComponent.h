// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SteeringMovementComponent.generated.h"


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

private:
    void DebugDraw(float DeltaTime);
    
protected:    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float InitialSpeed = 200;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float InitialAcceleration = 200;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
    bool bDebugEnable = true;
    
protected:
    UPROPERTY()
    AActor* Target;

    FVector CurrentVelocity = FVector::Zero();
    FVector CurrentAcceleration = FVector::Zero();
};