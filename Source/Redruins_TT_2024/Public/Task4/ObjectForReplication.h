// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObjectForReplication.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class REDRUINS_TT_2024_API UObjectForReplication : public UObject
{
    GENERATED_BODY()

public:
    FString ToString() const;
    virtual bool IsSupportedForNetworking () const override { return true; }
    virtual void GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
public:
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
    bool Value1;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
    float Value2;
    
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
    int32 Value3;
};
