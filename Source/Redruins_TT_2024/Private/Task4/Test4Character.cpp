// RedRuins Softworks (c)


#include "Task4/Test4Character.h"


ATest4Character::ATest4Character()
{
    PrimaryActorTick.bCanEverTick = false;
    SetReplicates(true);
}

void ATest4Character::BeginPlay()
{
    Super::BeginPlay();
}
