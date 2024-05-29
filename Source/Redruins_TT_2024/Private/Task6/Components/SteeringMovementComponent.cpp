// RedRuins Softworks (c)


#include "Task6/Components/SteeringMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Task6/Interfaces/PhysicalObject.h"

DEFINE_LOG_CATEGORY(LogSteeringMovementComponent);

USteeringMovementComponent::USteeringMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USteeringMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    check(GetOwner());
    SetComponentTickEnabled(false);

    TArray<TObjectPtr<AActor>> Objects;
    UGameplayStatics::GetAllActorsWithInterface(GetOwner(), UPhysicalObject::StaticClass(), Objects);
    check(Objects.Num() > 0);

    for (auto Object : Objects)
    {
        if (Object->ActorHasTag("Target"))
        {
            Target = Object;
            continue;
        }

        if (Object == GetOwner())
        {
            continue;
        }
        
        DynamicObjects.Add(Object);
    }

    check(Target);
    SetObservation(Target);
    Start();
}

void USteeringMovementComponent::HandleCollision(const FHitResult& InHitResult)
{
    CurrentAcceleration = InHitResult.ImpactNormal * CollisionImpactFactor;

    if (InHitResult.GetActor())
    {
        UE_LOG(LogSteeringMovementComponent, Display, TEXT("%s Collided with %s"), *GetName(), *InHitResult.GetActor()->GetName())
    }
}

FVector USteeringMovementComponent::GetTargetAcceleration() const
{
    const FVector CurrentTargetRadiusVector = Target->GetActorLocation() - GetOwner()->GetActorLocation();
    return CurrentTargetRadiusVector.GetSafeNormal() * IPhysicalObject::Execute_GetAccelerationFactor(Target);
}

FVector USteeringMovementComponent::GetDynamicObjectsAcceleration() const
{
    FVector AverageAccelerationDirection = FVector::Zero();
    for (auto DynamicObject : DynamicObjects)
    {
        const FVector CurrentTargetRadiusVector = DynamicObject->GetActorLocation() - GetOwner()->GetActorLocation();
        AverageAccelerationDirection += CurrentTargetRadiusVector.GetSafeNormal() * IPhysicalObject::Execute_GetAccelerationFactor(DynamicObject);
    }

    return AverageAccelerationDirection;
}

void USteeringMovementComponent::DebugDraw(float DeltaTime)
{
    CurrentDebugTime += DeltaTime;
    if (CurrentDebugTime < DebugEverySeconds)
    {
        return;
    }
    
    const FVector CurrentLocation = GetOwner()->GetActorLocation();

    DrawDebugLine(GetWorld(), CurrentLocation, CurrentLocation + CurrentVelocity.GetSafeNormal() * DebugLineLength, FColor::Red , false, 5, 0, 2);
    DrawDebugLine(GetWorld(), CurrentLocation, CurrentLocation + CurrentAcceleration.GetSafeNormal() * DebugLineLength, FColor::Green , false, 5, 0, 2);

    CurrentDebugTime = 0.0f;
}

void USteeringMovementComponent::SetObservation(AActor* InTarget)
{
    Target = InTarget;
}

void USteeringMovementComponent::Start()
{
    check(Target);

    CurrentVelocity = GetInitialMovementDirection() * InitialSpeed;
    UpdateAcceleration();
    
    SetComponentTickEnabled(true);
}

void USteeringMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateVelocity(DeltaTime);

    const FVector CurrentLocation = GetOwner()->GetActorLocation();
    const FVector NewLocation = CurrentLocation + CurrentVelocity * DeltaTime;

    const FVector DeltaLocation = NewLocation - CurrentLocation;
    const FRotator NewRotation = GetRotatorFromDeltaLocation(DeltaLocation);

    FHitResult SweepHitResult;
    GetOwner()->SetActorLocation(NewLocation, true, &SweepHitResult);
    GetOwner()->SetActorRotation(NewRotation);

    if (bDebugEnable)
    {
        DebugDraw(DeltaTime);
    }

    UpdateAcceleration();
    if (SweepHitResult.bBlockingHit)
    {
        HandleCollision(SweepHitResult);
    }
}

void USteeringMovementComponent::UpdateAcceleration()
{
    const FVector TargetAcceleration = GetTargetAcceleration();
    const FVector DynamicObjectsAcceleration = GetDynamicObjectsAcceleration();
    const FVector NewAcceleration = TargetAcceleration + DynamicObjectsAcceleration;
    CurrentAcceleration = NewAcceleration;
}

void USteeringMovementComponent::UpdateVelocity(float DeltaTime)
{
    const FVector DeltaVelocity = CurrentAcceleration * DeltaTime;
    CurrentVelocity = CurrentVelocity + DeltaVelocity;
}

FRotator USteeringMovementComponent::GetRotatorFromDeltaLocation(const FVector& InDeltaLocation) const
{
    switch (ForwardAxis)
    {
        case EAxis::X: return UKismetMathLibrary::MakeRotFromX(InDeltaLocation);
        case EAxis::Y: return UKismetMathLibrary::MakeRotFromY(InDeltaLocation);
        case EAxis::Z: return UKismetMathLibrary::MakeRotFromZ(InDeltaLocation);
    }

    checkNoEntry()
    return {};
}

FVector USteeringMovementComponent::GetInitialMovementDirection() const
{
    switch (ForwardAxis)
    {
        case EAxis::X: return GetOwner()->GetActorForwardVector();
        case EAxis::Y: return GetOwner()->GetActorRightVector();
        case EAxis::Z: return GetOwner()->GetActorUpVector();
    }

    checkNoEntry()
    return {};
}
