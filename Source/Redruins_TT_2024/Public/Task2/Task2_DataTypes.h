// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Task2_DataTypes.generated.h"

class UDA_2;

USTRUCT(BlueprintType)
struct FGigaStruct
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UDA_2* DA_2_HardRef;
    
    UPROPERTY(EditDefaultsOnly, meta = (AllowedClasses = "DA_2"))
    TSoftObjectPtr<UDA_2> DA_2_SoftRef;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float ImField;
};

UENUM(BlueprintType)
enum class EGigaEnum : uint8
{
    value_true = 0 UMETA(DisplayName = "Value true"),
    value_false UMETA(DisplayName = "Value false"),
    value_n UMETA(DisplayName = "Value n")
};
