/*
Hazard code written by Ibrahim Al Rai
Code that deals with map hazards against the player
*/
#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Hazard.generated.h"

UCLASS()
class WHIMSICALWIZARDRY_API AHazard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHazard();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* HazardMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCapsuleComponent* HazardHitbox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LaunchScale = 500;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
};

