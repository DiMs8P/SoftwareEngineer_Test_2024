// RedRuins Softworks (c)


#include "Task5/Projectile.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(LifeTime);
}
