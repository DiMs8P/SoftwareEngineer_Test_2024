// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Task2_DataTypes.h"
#include "Engine/DataAsset.h"
#include "DA_2.generated.h"

class UDA_1;
/**
 * 
 */
UCLASS(BlueprintType)
class REDRUINS_TT_2024_API UDA_2 : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly)
    EGigaEnum GigaEnum;

    /*UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "GigaEnum == EGigaEnum::value_true", EditConditionHides))
    UDA_1* DA_1;*/

    // it also works with hard ref
    UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "GigaEnum == EGigaEnum::value_true", EditConditionHides, AllowedClasses = "DA_1"))
    TSoftObjectPtr<UDA_1> DA_1;
};
