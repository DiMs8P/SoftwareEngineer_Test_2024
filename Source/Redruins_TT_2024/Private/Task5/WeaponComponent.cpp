// RedRuins Softworks (c)


#include "Task5/WeaponComponent.h"

#include "Task5/Projectile.h"

DEFINE_LOG_CATEGORY(LogWeaponComponent);

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::Fire()
{
    check(ProjectileClass);
    FVector MuzzleLocation;
    FRotator MuzzleRotator;
    GetMuzzleTransform(MuzzleLocation, MuzzleRotator);

    Server_Fire(MuzzleLocation, MuzzleRotator);
}

void UWeaponComponent::Server_Fire_Implementation(const FVector& InMuzzleLocation, const FRotator& InMuzzleRotation)
{
    const FTransform SpawnTransform(InMuzzleRotation, InMuzzleLocation);
    AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetInitialVelocity(GetProjectileVelocity());
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}

void UWeaponComponent::SetProjectile(TSubclassOf<AProjectile> InProjectileClass)
{
    ProjectileClass = InProjectileClass;
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
