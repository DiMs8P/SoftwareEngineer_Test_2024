// RedRuins Softworks (c)


#include "Task6/Components/SteeringMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Task1/Observable.h"

USteeringMovementComponent::USteeringMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USteeringMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    check(GetOwner());
    SetComponentTickEnabled(false);

    TArray<TObjectPtr<AActor>> Targets;
    UGameplayStatics::GetAllActorsWithInterface(GetOwner(), UObservable::StaticClass(), Targets);
    check(Targets.Num() > 0);

    SetObservation(Targets[0]);
    Start();
}

void USteeringMovementComponent::DebugDraw(float DeltaTime)
{
    const FVector CurrentLocation = GetOwner()->GetActorLocation();

    DrawDebugLine(GetWorld(), CurrentLocation, CurrentLocation + CurrentVelocity.GetSafeNormal() * bDebugLineLength, FColor::Red , false, 5, 0, 2);
    DrawDebugLine(GetWorld(), CurrentLocation, CurrentLocation + CurrentAcceleration.GetSafeNormal() * bDebugLineLength, FColor::Green , false, 5, 0, 2);
}

void USteeringMovementComponent::SetObservation(AActor* InTarget)
{
    Target = InTarget;
}

void USteeringMovementComponent::Start()
{
    check(Target);

    CurrentVelocity = GetOwner()->GetActorForwardVector() * InitialSpeed;
    CurrentAcceleration = (IObservable::Execute_GetObservationLocation(Target) - GetOwner()->GetActorLocation()).GetSafeNormal() * InitialAcceleration;
      
    SetComponentTickEnabled(true);
}

void USteeringMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentAcceleration = (IObservable::Execute_GetObservationLocation(Target) - GetOwner()->GetActorLocation()).GetSafeNormal() * InitialAcceleration;

    const FVector DeltaVelocity = CurrentAcceleration * DeltaTime;
    CurrentVelocity = CurrentVelocity + DeltaVelocity;

    const FVector CurrentLocation = GetOwner()->GetActorLocation();
    const FVector NewLocation = CurrentLocation + CurrentVelocity * DeltaTime;

    const FVector DeltaLocation = NewLocation - CurrentLocation;
    FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(DeltaLocation);
    
    GetOwner()->SetActorLocation(NewLocation);
    GetOwner()->SetActorRotation(NewRotation);

    if (bDebugEnable)
    {
        DebugDraw(DeltaTime);
    }
}
