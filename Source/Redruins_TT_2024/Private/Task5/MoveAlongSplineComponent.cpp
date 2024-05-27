// RedRuins Softworks (c)


#include "Task5/MoveAlongSplineComponent.h"

#include "Components/SplineComponent.h"
#include "GameFramework/MovementComponent.h"

DEFINE_LOG_CATEGORY(LogMoveAlongSplineComponent);

UMoveAlongSplineComponent::UMoveAlongSplineComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMoveAlongSplineComponent::BeginPlay()
{
    Super::BeginPlay();
    SetComponentTickEnabled(false);

    check(GetOwner());
    OwnerMovementComponent = GetOwner()->GetComponentByClass<UMovementComponent>();
    check(OwnerMovementComponent);
}

void UMoveAlongSplineComponent::Start()
{
    check(Spline)
    check(MinSpeed <= MaxSpeed)
    check(MinSpeed >= 0)
    check(InitialSpeed <= MaxSpeed && InitialSpeed >= MinSpeed)

    SplineComponent = Spline->GetComponentByClass<USplineComponent>();
    check(SplineComponent)

    CurrentSpeed = InitialSpeed;
    CurrentDistanceOnSpline = 0.0f;
    CurrentVelocity = FVector::Zero();

    GetOwner()->SetActorLocation(SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistanceOnSpline, ESplineCoordinateSpace::World));
    SetComponentTickEnabled(true);
}

void UMoveAlongSplineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    MoveAlongSpline(DeltaTime);
}

void UMoveAlongSplineComponent::MoveAlongSpline(float DeltaTime)
{
    const FVector OldLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistanceOnSpline, ESplineCoordinateSpace::World);
    CurrentDistanceOnSpline += CurrentSpeed * DeltaTime;

    const float SplineLength = SplineComponent->GetSplineLength();
    if (CurrentDistanceOnSpline > SplineLength)
    {
        CurrentDistanceOnSpline -= SplineLength;
    }

    const FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistanceOnSpline, ESplineCoordinateSpace::World);
    CurrentVelocity = (NewLocation - OldLocation) / DeltaTime;

    const float HeightAdjustment = NewLocation.Z - OldLocation.Z;
    GetOwner()->SetActorLocation(FVector(NewLocation.X, NewLocation.Y, GetOwner()->GetActorLocation().Z + HeightAdjustment));
}

void UMoveAlongSplineComponent::AdjustSpeed(const float InSpeedAdjustment)
{
    CurrentSpeed = FMath::Clamp(CurrentSpeed + InSpeedAdjustment, MinSpeed, MaxSpeed);
}

FVector UMoveAlongSplineComponent::GetCurrentVelocity()
{
    return CurrentVelocity;
}
