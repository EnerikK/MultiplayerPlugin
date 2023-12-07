// Hello :)


#include "Framework/UI/MPCommonButtonBase.h"
#include "CommonTextBlock.h"
#include "CommonBorder.h"
#include "Framework/Data/StaticGameData.h"

void UMPButtonBaseWidget::SetButtonText(const FText& InText)
{
	bOverride_ButtonText = false;
	ButtonText = InText;
	UpdateButtonText(ButtonText);
}

void UMPButtonBaseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	InitButton();
}

void UMPButtonBaseWidget::InitButton()
{
	OnHovered().AddUObject(this,&UMPButtonBaseWidget::OnButtonHovered);
	OnUnhovered().AddUObject(this,&UMPButtonBaseWidget::OnButtonUnHovered);

	ApplyMaterial();
	UpdateButtonText(ButtonText);
	SetButtonSettings();
}

void UMPButtonBaseWidget::OnButtonHovered()
{
	if(ButtonBorder != nullptr)
	{
		if(UMaterialInstanceDynamic* MaterialInstance = ButtonBorder->GetDynamicMaterial())
		{
			MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_HOVER,1.f);
		}
	}
	
}

void UMPButtonBaseWidget::OnButtonUnHovered()
{
	if(ButtonBorder != nullptr)
	{
		if(UMaterialInstanceDynamic* MaterialInstance = ButtonBorder->GetDynamicMaterial())
		{
			MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_HOVER,0.f);
		}
	}
	
	
}

void UMPButtonBaseWidget::ApplyMaterial() const
{
	if(ButtonBorder != nullptr && Material != nullptr)
	{
		ButtonBorder->SetBrushFromMaterial(Material);
	}
}

void UMPButtonBaseWidget::UpdateButtonText(const FText& InText)
{
	if(ButtonTextBlock)
	{
		ButtonTextBlock->SetText(InText);
	}
}

void UMPButtonBaseWidget::SetButtonSettings() const
{
	if(ButtonBorder != nullptr)
	{
		if(UMaterialInstanceDynamic* MaterialInstance = ButtonBorder->GetDynamicMaterial())
		{
			if(bOverride_Texture_Alpha > 0)
			{
				MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_TEX_ALPHA,TextureAlpha);
				MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_TEX_ALPHA_HOVER,TextureHoverAlpha);

			}
			if(bOverride_Texture_Scale > 0)
			{
				MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_TEX_SCALE,TextureScale);
				MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_TEX_SCALE_HOVER,TextureHoverScale);
				
			}
			if(bOverride_Texture_Shift > 0)
			{
				MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_TEX_SHIFT_X,TextureShiftX);
				MaterialInstance->SetScalarParameterValue(MP_MAT_PARAM_NAME_TEX_SHIFT_Y,TextureShiftY);
				
			}
			if(ButtonTexture != nullptr)
			{
				MaterialInstance->SetTextureParameterValue(MP_MAT_PARAM_NAME_TEXTURE,ButtonTexture);
			}
		}
	}
}
