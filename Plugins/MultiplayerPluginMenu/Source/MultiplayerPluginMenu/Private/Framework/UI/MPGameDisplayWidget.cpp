// Hello :)


#include "Framework/UI/MPGameDisplayWidget.h"

void UMPGameDisplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GameButtonWidget.IsValidLowLevel())
	{
		GameButtonWidget.OnClicked().AddUObject(this,&UMPGameDisplayWidget::OnGameSelection);
	}
}

void UMPGameDisplayWidget::SetGameData(const FPrimaryAssetId& Data)
{
	if(Data.IsValid() && GameButtonWidget)
	{
		
	}
}

void UMPGameDisplayWidget::OnGameSelection()
{
	OnGameDisplaySelected.Broadcast(GameDataId);
}
