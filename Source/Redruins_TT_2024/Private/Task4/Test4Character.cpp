// RedRuins Softworks (c)


#include "Task4/Test4Character.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"
#include "Task5/Projectile.h"
#include "Task5/WeaponComponent.h"


ATest4Character::ATest4Character()
{
    PrimaryActorTick.bCanEverTick = false;
    SetReplicates(true);
}

void ATest4Character::CreateComponent()
{
    if (HasAuthority())
    {
        WeaponComponent = NewObject<UWeaponComponent>(this, TEXT("DynamicWeaponComponent"));
        AddInstanceComponent(WeaponComponent);
        WeaponComponent->RegisterComponent();
    
        OnRep_WeaponComponent();
    }
}

void ATest4Character::ChangeObjectValues()
{
}

void ATest4Character::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ATest4Character::OnRep_WeaponComponent()
{
    if (WeaponComponent)
    {
        check(ProjectileClass);
        WeaponComponent->SetProjectile(ProjectileClass);
    }
}

void ATest4Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATest4Character, WeaponComponent);
}

void ATest4Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Firing
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATest4Character::Fire);
    }
}

void ATest4Character::Fire(const FInputActionValue& Value)
{
    if (WeaponComponent)
    {
        WeaponComponent->Fire();
    }
}
