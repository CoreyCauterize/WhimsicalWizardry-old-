// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WhimsicalWizardryGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AWhimsicalWizardryGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
        AWhimsicalWizardryGameModeBase();

		virtual void PostLogin(APlayerController* NewPlayer) override;

		virtual void Logout(AController* Exiting) override;


		virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

		UFUNCTION(NetMultiCast, Reliable)
            void NMC_SpawnPlayerCamera(APlayerController* NewPlayer);

		FORCEINLINE TSubclassOf<class ADynamicCamera> GetDynamicCameraClass() const { return DynamicCameraClass; }

private:	

	UPROPERTY(EditDefaultsOnly, Category = "Player Camera", meta = (AllowPrivateAccess ="true"))
	TSubclassOf<class ADynamicCamera> DynamicCameraClass;


};
