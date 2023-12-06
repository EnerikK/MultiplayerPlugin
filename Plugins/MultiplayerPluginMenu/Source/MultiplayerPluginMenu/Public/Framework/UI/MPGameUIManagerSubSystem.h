// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "MPGameUIManagerSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGINMENU_API UMPGameUIManagerSubSystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()

public:

	UMPGameUIManagerSubSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:

	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	FTSTicker::FDelegateHandle TickHandle;
	
};
