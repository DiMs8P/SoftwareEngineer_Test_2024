// RedRuins Softworks (c)


#include "Task1/Components/ObservationComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Task1/Actors/InterestPoint.h"

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

    GetInitialObservations(CurrentObservations);
    for (auto Observation : CurrentObservations)
    {
        Observation->Enable();
    }
}

void UObservationComponent::GetInitialObservations(TArray<AInterestPoint*>& OutObservations) const
{
    TArray<AActor*> Observations;
    UGameplayStatics::GetAllActorsOfClass(GetOwner(), AInterestPoint::StaticClass(), Observations);

    for (AActor* Observation : Observations)
    {
        if (AInterestPoint* InterestPoint = Cast<AInterestPoint>(Observation))
        {
            OutObservations.Add(InterestPoint);
        }
    }
}
