// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test4Character.generated.h"

class UObjectForReplication;
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
    virtual bool ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void CreateComponent();
    
    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ChangeObjectValues();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void Fire(const FInputActionValue& Value);

protected:
    UFUNCTION(BlueprintCallable)
    void SetObjectForReplication(UObjectForReplication* InObjectForReplication);

private:
    UFUNCTION()
    void OnRep_WeaponComponent();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* FireAction;

protected:
    UPROPERTY(ReplicatedUsing=OnRep_WeaponComponent, Transient, EditDefaultsOnly, BlueprintReadWrite)
    UWeaponComponent* WeaponComponent;
    
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
    UObjectForReplication* ObjectForReplication;
};