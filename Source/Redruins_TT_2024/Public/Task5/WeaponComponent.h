// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWeaponComponent, All, All)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWeaponComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Fire();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void GetMuzzleTransform(FVector& OutMuzzleLocation, FRotator& OutMuzzleRotator) const;

    UFUNCTION(BlueprintCallable)
    FVector GetProjectileVelocity() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletInitialVelocity = 2000;

private:
    static constexpr float MuzzleOffset = 100.0f;
};