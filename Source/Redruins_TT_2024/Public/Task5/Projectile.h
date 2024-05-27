// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class REDRUINS_TT_2024_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    AProjectile();

    UFUNCTION(BlueprintImplementableEvent)
    void Initialize(const FVector& InInitialVelocity);

protected:
    virtual void BeginPlay() override;

protected:
    float LifeTime = 10.0f;
};