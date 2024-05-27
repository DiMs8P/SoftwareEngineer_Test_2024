// RedRuins Softworks (c)


#include "Task1/Components/ObservationComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Shared/SharedFunctionLibrary.h"
#include "Task1/Observable.h"
#include "Task1/Widgets/PointOfInterest.h"

UObservationComponent::UObservationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UObservationComponent::BeginPlay()
{
    Super::BeginPlay();

    const APawn* Owner = Cast<APawn>(GetOwner());
    check(Owner);
    if (!Owner->IsPlayerControlled())
    {
        SetComponentTickEnabled(false);
        return;
    }

    TArray<TScriptInterface<IObservable>> InitialObservations;
    GetInitialObservations(InitialObservations);
    for (auto Observation : InitialObservations)
    {
        TObjectPtr<UPointOfInterest> ObservationMarkerInstance = USharedFunctionLibrary::SetupWidgetInstanceChecked<UPointOfInterest>(GetOwner(), ObservationMarkerWidgetClass);
        ObservationMarkerInstance->SetObservation(Observation);
        
        CurrentObservations.Add(Observation, ObservationMarkerInstance);
    }
}

void UObservationComponent::GetInitialObservations(TArray<TScriptInterface<IObservable>>& OutObservations) const
{
    // You can get em from Subsystem or somewhere else
    // You can bind to some game events e.g. OnObservationAdded or others
    // You also can ask for current player target place here e.g. PlayerObservationSubsystem->GetCurrentObservation()
    TArray<TObjectPtr<AActor>> Observations;
    UGameplayStatics::GetAllActorsWithInterface(GetOwner(), UObservable::StaticClass(), Observations);

    for (const auto Observation : Observations)
    {
        TScriptInterface<IObservable> InterfaceInstance (Observation);
        OutObservations.Add(InterfaceInstance);
    }
}
