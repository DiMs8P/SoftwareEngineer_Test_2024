// RedRuins Softworks (c)


#include "Task4/Test4Character.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/ActorChannel.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Task4/ObjectForReplication.h"
#include "Task5/Projectile.h"
#include "Task5/WeaponComponent.h"


ATest4Character::ATest4Character()
{
    PrimaryActorTick.bCanEverTick = true;
    SetReplicates(true);
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

void ATest4Character::Tick(float DeltaSeconds)
{
    if (!ObjectForReplication)
    {
        return;
    }
    
    if (HasAuthority())
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Server: %s"), *ObjectForReplication->ToString()), true, false, FColor::Blue, 0);
    }
    else
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Client: %s"), *ObjectForReplication->ToString()), true, false, FColor::Orange, 0);
    }

    Super::Tick(DeltaSeconds);
}

void ATest4Character::ChangeObjectValues_Implementation()
{
    check(ObjectForReplication);
    ObjectForReplication->Value1 = UKismetMathLibrary::RandomBool();
    ObjectForReplication->Value2 = UKismetMathLibrary::RandomFloat();
    ObjectForReplication->Value3 = UKismetMathLibrary::RandomInteger(INT_MAX);
}

void ATest4Character::CreateComponent_Implementation()
{
    if (WeaponComponent)
    {
        return;
    }

    check(ProjectileClass);
    WeaponComponent = NewObject<UWeaponComponent>(this, TEXT("DynamicWeaponComponent"));
    AddInstanceComponent(WeaponComponent);
    WeaponComponent->RegisterComponent();
    
    OnRep_WeaponComponent();
}

void ATest4Character::OnRep_WeaponComponent()
{
    check(WeaponComponent)
    if (WeaponComponent)
    {
        WeaponComponent->SetProjectile(ProjectileClass);
    }
    
    if (HasAuthority())
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Server: Created component %s"), *WeaponComponent->GetName()), true, false, FColor::Green, 3);
    }
    else
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Client: Created component %s"), *WeaponComponent->GetName()), true, false, FColor::Yellow, 3);
    }
}

void ATest4Character::SetObjectForReplication(UObjectForReplication* InObjectForReplication)
{
    check(HasAuthority())
    ObjectForReplication = InObjectForReplication;
}

void ATest4Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATest4Character, WeaponComponent);
    DOREPLIFETIME(ATest4Character, ObjectForReplication);
}

bool ATest4Character::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    check(ObjectForReplication)
    bWroteSomething |= Channel->ReplicateSubobject(ObjectForReplication , *Bunch, *RepFlags);

    return bWroteSomething;
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
