// Hello :)


#include "Framework/UI/MPGameDisplayWidget.h"
#include "Framework/UI/MPButtonGameWidget.h"

void UMPGameDisplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GameButtonWidget)
	{
		GameButtonWidget->OnClicked().AddUObject(this,&UMPGameDisplayWidget::OnGameSelection);
	}
	
	
}

void UMPGameDisplayWidget::SetGameData(const FPrimaryAssetId& Data)
{
	if(Data.IsValid() && GameButtonWidget)
	{
		GameDataId = Data;
		GameButtonWidget->SetGameData(Data);
		
	}
}

void UMPGameDisplayWidget::OnGameSelection()
{
	OnGameDisplaySelected.Broadcast(GameDataId);
}
