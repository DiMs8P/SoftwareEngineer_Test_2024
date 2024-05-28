// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDRUINS_TT_2024_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();
    
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Interact();

    UFUNCTION(BlueprintCallable)
    AActor* GetActorToInteractWith() const;

protected:
	virtual void BeginPlay() override;

	bool GetActorToInteractWith_Internal(AActor*& OutInteractActor) const;
	
	bool IsHitResultValid(const FHitResult& InHitResult) const;
	
	bool GetControllerViewHitResult(FHitResult& OutHitResult) const;
	void GetControllerViewTraceLocations(FVector& OutStartLocation, FVector& OutEndLocation) const;
	void GetControllerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	bool GetPlayerViewHitResult(FHitResult& OutHitResult, const FVector& InImpactPointLocation) const;
	void GetPlayerViewTraceLocations(FVector& OutStartLocation, FVector& OutEndLocation, const FVector& InImpactPoint) const;
	void GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	void GetLineTraceHitResult(FHitResult& OutHitResult, const FVector& InStartLocation, const FVector& InEndLocation) const;
	bool GetHitResult_Internal(FHitResult& OutHitResult, const FVector& InStartLocation, const FVector& InEndLocation) const;

    void TryNotifyPostInteraction(AActor* PrevFocusedActor) const;
    void TryNotifyPreInteraction(const AActor* PrevFocusedActor) const;

	APawn* GetOwnerChecked() const;
	APlayerController* GetControllerChecked() const;

protected:
	UPROPERTY()
	AActor* FocusedActor;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
	bool bDebugEnable = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
	float ControllerViewTraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
	float PlayerViewTraceMaxDistance = 100.0f;
};
