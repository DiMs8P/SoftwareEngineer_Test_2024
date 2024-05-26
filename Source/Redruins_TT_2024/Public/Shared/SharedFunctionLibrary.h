// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "SharedFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class REDRUINS_TT_2024_API USharedFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    template<typename T>
    static TObjectPtr<T> SetupWidgetInstanceChecked(const UObject* InWorldContextObject, const TSubclassOf<T>& InWidgetClass)
    {
        UWorld* World = InWorldContextObject->GetWorld();
        check(World);
        TObjectPtr<T> WidgetInstance = CreateWidget<T>(World, InWidgetClass);
        check(WidgetInstance);
	
        WidgetInstance->AddToViewport();
        WidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
        return WidgetInstance;
    }
};
