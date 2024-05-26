// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Task2_DataTypes.h"
#include "Engine/DataAsset.h"
#include "DA_1.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class REDRUINS_TT_2024_API UDA_1 : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly)
    FGigaStruct GigaStruct;
};
