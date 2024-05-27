// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

class UMoveAlongSplineComponent;

UCLASS()
class REDRUINS_TT_2024_API ATestCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATestCharacter();

    virtual FVector GetVelocity() const override;
    
protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool bAffectCharacterVelocity = false;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TObjectPtr<UMoveAlongSplineComponent> MoveAlongSplineComponent;
};