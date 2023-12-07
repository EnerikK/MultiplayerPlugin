// Hello :)

#pragma once

#include "NativeGameplayTags.h"

//Asset Manager data types
#define MP_DATA_ASSET_TYPE_GAMEDATA		    FName(TEXT("GameData"))
#define MP_DATA_ASSET_TYPE_GAMEDATA_DEFAULT FName(TEXT("DA_GameData_Default"))

//Multiplayer Settings
#define MP_MP_SETTINGS_GAMEMODE				TEXT("GAMEMODE")

//Asset Bundles
#define MP_DATA_ASSET_BUNDLE_GAME			FName(TEXT("Game"))

namespace UILayerTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_GAME);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_GAMEMENU);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_MENU);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_MODAL);
}

//Material Param References
#define MP_MAT_PARAM_NAME_TEXTURE			FName(TEXT("Texture"))
#define MP_MAT_PARAM_NAME_HOVER				FName(TEXT("HoverAnimate"))
#define MP_MAT_PARAM_NAME_TEX_ALPHA			FName(TEXT("TextureAlpha"))
#define MP_MAT_PARAM_NAME_TEX_ALPHA_HOVER	FName(TEXT("TextureAlphaHover"))
#define MP_MAT_PARAM_NAME_TEX_SCALE			FName(TEXT("TextureScale"))
#define MP_MAT_PARAM_NAME_TEX_SCALE_HOVER	FName(TEXT("TextureHoverScale"))
#define MP_MAT_PARAM_NAME_TEX_SHIFT_X		FName(TEXT("Shift_X"))
#define MP_MAT_PARAM_NAME_TEX_SHIFT_Y		FName(TEXT("Shift_Y"))