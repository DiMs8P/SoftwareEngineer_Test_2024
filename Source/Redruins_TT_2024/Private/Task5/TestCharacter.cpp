// RedRuins Softworks (c)


#include "Task5/TestCharacter.h"

#include "Task5/MoveAlongSplineComponent.h"


ATestCharacter::ATestCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    MoveAlongSplineComponent = CreateDefaultSubobject<UMoveAlongSplineComponent>(TEXT("MoveAlongSplineComponent"));
}

FVector ATestCharacter::GetVelocity() const
{
    // Due to the fact that the position of the actor changes using SetActorLocation,
    // even with small changes in position,
    // the velocity vector can quite abruptly change its direction,
    // which leads to strong jerks. I didn't waste time solving this problem
    if (bAffectCharacterVelocity)
    {
        return MoveAlongSplineComponent->GetCurrentVelocity();
    }

    return FVector::Zero();
}

void ATestCharacter::BeginPlay()
{
    Super::BeginPlay();
}
