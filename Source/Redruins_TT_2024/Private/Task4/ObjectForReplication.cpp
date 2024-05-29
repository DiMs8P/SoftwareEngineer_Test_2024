// RedRuins Softworks (c)


#include "Task4/ObjectForReplication.h"

#include "Net/UnrealNetwork.h"

FString UObjectForReplication::ToString() const
{
    return FString::Printf(TEXT("Value1: %s, Value2: %f, Value3: %d"), Value1 ? TEXT("True") : TEXT("False"), Value2, Value3);
}

void UObjectForReplication::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UObjectForReplication, Value1);
    DOREPLIFETIME(UObjectForReplication, Value2);
    DOREPLIFETIME(UObjectForReplication, Value3);

    if (UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass()))
    {
        BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
    }
}