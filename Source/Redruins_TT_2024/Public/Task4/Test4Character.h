// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test4Character.generated.h"

UCLASS()
class REDRUINS_TT_2024_API ATest4Character : public ACharacter
{
    GENERATED_BODY()

public:
    ATest4Character();
    
    void CreateComponent();

protected:
    virtual void BeginPlay() override;
};