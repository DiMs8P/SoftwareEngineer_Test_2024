// RedRuins Softworks (c)


#include "Task5/Projectile.h"

#include "Net/UnrealNetwork.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    SetReplicates(true);
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(LifeTime);
}

void AProjectile::SetInitialVelocity_Implementation(const FVector& InInitialVelocity)
{
    check(HasAuthority())
    InitialVelocity = InInitialVelocity;
}

void AProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AProjectile, InitialVelocity);
}
