﻿// RedRuins Softworks (c)


#include "Task5/WeaponComponent.h"

#include "Shared/SharedFunctionLibrary.h"
#include "Task5/Projectile.h"

DEFINE_LOG_CATEGORY(LogWeaponComponent);

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    check(ProjectileClass);
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::Fire()
{
    FVector MuzzleLocation;
    FRotator MuzzleRotator;
    GetMuzzleTransform(MuzzleLocation, MuzzleRotator);
    
    const FTransform SpawnTransform(MuzzleRotator, MuzzleLocation);
    AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->Initialize(GetProjectileVelocity());
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}

void UWeaponComponent::GetMuzzleTransform(FVector& OutMuzzleLocation, FRotator& OutMuzzleRotator) const
{
    GetOwner()->GetActorEyesViewPoint(OutMuzzleLocation, OutMuzzleRotator);
    OutMuzzleLocation += OutMuzzleRotator.Vector() * MuzzleOffset;
}

FVector UWeaponComponent::GetProjectileVelocity() const
{
    const FVector OwnerVelocity = GetOwner()->GetVelocity();

    FVector MuzzleLocation;
    FRotator MuzzleRotator;
    GetMuzzleTransform(MuzzleLocation, MuzzleRotator);

    const FVector ProjectileVelocity = MuzzleRotator.Vector() * BulletInitialVelocity;

    UE_LOG(LogWeaponComponent, Display, TEXT("Owner velocity: %s"), *OwnerVelocity.ToString());
    UE_LOG(LogWeaponComponent, Display, TEXT("ProjectileVelocity velocity: %s"), *ProjectileVelocity.ToString());
    return OwnerVelocity + ProjectileVelocity;
}
