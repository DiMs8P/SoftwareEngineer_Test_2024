// RedRuins Softworks (c)


#include "Task1/Widgets/InteractLable.h"

void UInteractLable::ShowLable(AActor* NewInteraction)
{
    if (IsVisible() || !NewInteraction)
    {
        return;
    }

    Interaction = NewInteraction;
    K2_ShowLable();
}

void UInteractLable::HideLable()
{
    if (!IsVisible())
    {
        return;
    }
    
    K2_HideLable();
}