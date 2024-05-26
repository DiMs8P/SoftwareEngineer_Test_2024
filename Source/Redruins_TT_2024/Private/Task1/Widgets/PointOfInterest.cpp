// RedRuins Softworks (c)


#include "Task1/Widgets/PointOfInterest.h"

#include "Task1/Observable.h"

void UPointOfInterest::SetObservation(TScriptInterface<IObservable> NewObservation)
{
    Observation = NewObservation;
    
    K2_SetObservation();
}