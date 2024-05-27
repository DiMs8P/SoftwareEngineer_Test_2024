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
    const FVector ObservationLocation = IObservable::Execute_GetObservationLocation(Target);
    const FVector Direction = CurrentVelocity.GetSafeNormal();

    const FVector RadiusVector = CurrentLocation - ObservationLocation;

    const float Radius = RadiusVector.Size();
    const float Speed = CurrentVelocity.Size();
    const float AngularSpeed = Speed / Radius;
    
    const float DeltaAngle = AngularSpeed * DeltaTime;
    const FVector RotationAxis = FVector::CrossProduct(RadiusVector, Direction).GetSafeNormal();
    const FQuat RotationQuat = FQuat(RotationAxis, DeltaAngle);
    
    const FVector NewRadiusVector = RotationQuat.RotateVector(RadiusVector);
    
    DrawDebugLine(GetWorld(), CurrentLocation, CurrentLocation + CurrentVelocity, FColor::Red , false, 5, 0, 2);
    DrawDebugLine(GetWorld(), ObservationLocation, ObservationLocation + RadiusVector, FColor::Green , false, 5, 0, 2);
    DrawDebugLine(GetWorld(), ObservationLocation, ObservationLocation + NewRadiusVector, FColor::Blue , false, 5, 0, 2);
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

    const FVector CurrentLocation = GetOwner()->GetActorLocation();
    const FVector ObservationLocation = IObservable::Execute_GetObservationLocation(Target);
    const FVector Direction = CurrentVelocity.GetSafeNormal();

    const FVector RadiusVector = CurrentLocation - ObservationLocation;

    const float Radius = RadiusVector.Size();
    const float Speed = CurrentVelocity.Size();
    const float AngularSpeed = Speed / Radius;
    
    const float DeltaAngle = AngularSpeed * DeltaTime;
    const FVector RotationAxis = FVector::CrossProduct(RadiusVector, Direction).GetSafeNormal();
    const FQuat RotationQuat = FQuat(RotationAxis, DeltaAngle);
    const FVector NewRadiusVector = RotationQuat.RotateVector(RadiusVector);
    
    const FVector NewLocation = ObservationLocation + NewRadiusVector;
    FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(NewRadiusVector - RadiusVector);
    
    GetOwner()->SetActorLocation(NewLocation);
    GetOwner()->SetActorRotation(NewRotation);

    CurrentVelocity = GetOwner()->GetActorForwardVector() * InitialSpeed;

    if (bDebugEnable)
    {
        DebugDraw(DeltaTime);
    }
}
