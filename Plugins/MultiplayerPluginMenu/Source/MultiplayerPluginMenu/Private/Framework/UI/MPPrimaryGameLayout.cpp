// Hello :)


#include "Framework/UI/MPPrimaryGameLayout.h"
#include "Framework/Data/StaticGameData.h"


void UMPPrimaryGameLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterLayer(UILayerTags::TAG_UI_LAYER_GAME,GameStack);
	RegisterLayer(UILayerTags::TAG_UI_LAYER_MENU,MenuStack);
	RegisterLayer(UILayerTags::TAG_UI_LAYER_GAMEMENU,GameMenuStack);
	RegisterLayer(UILayerTags::TAG_UI_LAYER_MODAL,ModalStack);
}
