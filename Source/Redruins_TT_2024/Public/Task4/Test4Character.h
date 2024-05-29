// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test4Character.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class AProjectile;
class UWeaponComponent;

UCLASS()
class REDRUINS_TT_2024_API ATest4Character : public ACharacter
{
    GENERATED_BODY()

public:
    ATest4Character();
    
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    void CreateComponent();

    UFUNCTION(BlueprintCallable)
    void ChangeObjectValues();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Fire(const FInputActionValue& Value);

private:
    UFUNCTION()
    void OnRep_WeaponComponent();

protected:
    UPROPERTY(ReplicatedUsing=OnRep_WeaponComponent, Transient, EditDefaultsOnly, BlueprintReadWrite)
    UWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* FireAction;
};