// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UArmComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UArmComponent();

protected:
    virtual void BeginPlay() override;
};