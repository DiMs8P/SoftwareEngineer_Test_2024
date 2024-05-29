// RedRuins Softworks (c)


#include "Task1/Widgets/PointOfInterest.h"

void UPointOfInterest::SetTargetLocation(const FVector& InTargetLocation)
{
    TargetLocation = InTargetLocation;
}

void UPointOfInterest::SetViewMode(const ViewMode InNewViewMode)
{
    TargetViewMode = InNewViewMode;
      
    K2_SetViewMode();
}
