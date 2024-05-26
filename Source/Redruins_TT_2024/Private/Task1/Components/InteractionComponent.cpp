// RedRuins Softworks (c)


#include "Task1/Components/InteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Shared/SharedFunctionLibrary.h"
#include "Task1/Interactable.h"
#include "Task1/Widgets/InteractLable.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwnerChecked()->IsPlayerControlled())
	{
		SetComponentTickEnabled(false);
	}

    InteractTipWidgetInstance = USharedFunctionLibrary::SetupWidgetInstanceChecked<UInteractLable>(GetOwner(), InteractTipWidgetClass);
}

bool UInteractionComponent::IsHitResultValid(const FHitResult& InHitResult) const
{
	return InHitResult.bBlockingHit && InHitResult.GetActor() && InHitResult.GetActor()->Implements<UInteractable>();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetActorToInteractWith_Internal(FocusedActor))
	{
		HideInteractWidget();
		return;
	}
	
    ShowInteractWidget();
}

void UInteractionComponent::Interact()
{
	if (!FocusedActor)
	{
		return;
	}

	IInteractable::Execute_Interact(FocusedActor);
}

AActor* UInteractionComponent::GetActorToInteractWith() const
{
    return FocusedActor;
}

bool UInteractionComponent::GetActorToInteractWith_Internal(AActor*& OutInteractActor) const
{
	OutInteractActor = nullptr;
	
	FHitResult ControllerViewHitResult;
	if (!GetControllerViewHitResult(ControllerViewHitResult))
	{
		return false;
	}

	FHitResult PlayerViewHitResult;
	if (!GetPlayerViewHitResult(PlayerViewHitResult, ControllerViewHitResult.ImpactPoint))
	{
		return false;
	}

	OutInteractActor = PlayerViewHitResult.GetActor();
	return true;
}

bool UInteractionComponent::GetControllerViewHitResult(FHitResult& OutHitResult) const
{
	FVector StartLocation;
	FVector EndLocation;
	GetControllerViewTraceLocations(StartLocation, EndLocation);

	return GetHitResult_Internal(OutHitResult, StartLocation, EndLocation);
}

void UInteractionComponent::GetControllerViewTraceLocations(FVector& OutStartLocation, FVector& OutEndLocation) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	GetControllerViewPoint(ViewLocation, ViewRotation);

	const FVector Direction = ViewRotation.Vector();

	OutStartLocation = ViewLocation;
	OutEndLocation = OutStartLocation + Direction * ControllerViewTraceMaxDistance;
}

void UInteractionComponent::GetControllerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const
{
	GetControllerChecked()->GetPlayerViewPoint(OutViewLocation, OutViewRotation);
}

bool UInteractionComponent::GetPlayerViewHitResult(FHitResult& OutHitResult, const FVector& InImpactPointLocation) const
{
	FVector StartLocation;
	FVector EndLocation;
	GetPlayerViewTraceLocations(StartLocation, EndLocation, InImpactPointLocation);

	return GetHitResult_Internal(OutHitResult, StartLocation, EndLocation);
}

void UInteractionComponent::GetPlayerViewTraceLocations(FVector& OutStartLocation, FVector& OutEndLocation, const FVector& InImpactPoint) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	GetPlayerViewPoint(ViewLocation, ViewRotation);

	FVector Direction = InImpactPoint - ViewLocation;
	Direction.Normalize();

	OutStartLocation = ViewLocation;
	OutEndLocation = OutStartLocation + Direction * PlayerViewTraceMaxDistance;
}

void UInteractionComponent::GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const
{
	GetOwnerChecked()->GetActorEyesViewPoint(OutViewLocation, OutViewRotation);
}

bool UInteractionComponent::GetHitResult_Internal(FHitResult& OutHitResult, const FVector& InStartLocation, const FVector& InEndLocation) const
{
	GetLineTraceHitResult(OutHitResult, InStartLocation, InEndLocation);
	
	if (!IsHitResultValid(OutHitResult))
	{
		if (bDebugEnable)
		{
			DrawDebugLine(GetWorld(), InStartLocation, InEndLocation, FColor::Red , false, 0, 0, 2);
		}
		return false;
	}
	
	if (bDebugEnable)
	{
		DrawDebugSphere(GetWorld(), OutHitResult.ImpactPoint, 5, 32, FColor::Black, false, 0.0f);
		DrawDebugLine(GetWorld(), InStartLocation, InEndLocation, FColor::Green , false, 0, 0, 2);
	}

	return true;
}

void UInteractionComponent::GetLineTraceHitResult(FHitResult& OutHitResult, const FVector& InStartLocation,
                                                  const FVector& InEndLocation) const
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(OutHitResult, InStartLocation, InEndLocation, ECC_Visibility, CollisionQueryParams);
}

void UInteractionComponent::HideInteractWidget() const
{
	check(InteractTipWidgetInstance);

    if (InteractTipWidgetInstance->IsVisible())
    {
        InteractTipWidgetInstance->HideLable();
    }
}

void UInteractionComponent::ShowInteractWidget() const
{
	check(InteractTipWidgetInstance);
    check(FocusedActor)

    if (!InteractTipWidgetInstance->IsVisible())
    {
        InteractTipWidgetInstance->ShowLable(FocusedActor);
    }
}

APawn* UInteractionComponent::GetOwnerChecked() const
{
	APawn* Owner = Cast<APawn>(GetOwner());
	check(Owner);

	return Owner;
}

APlayerController* UInteractionComponent::GetControllerChecked() const
{
	APawn* Owner = GetOwnerChecked();
	
	APlayerController* Controller = Owner->GetController<APlayerController>();
	check(Controller);

	return Controller;
}
