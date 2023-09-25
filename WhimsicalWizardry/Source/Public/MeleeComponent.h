// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Components/ActorComponent.h"
#include "MeleeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHIMSICALWIZARDRY_API UMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeComponent();

	UPROPERTY()
	class UStaticMeshComponent* meleeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force Applied");
	class URadialForceComponent* meleeKnockback;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
