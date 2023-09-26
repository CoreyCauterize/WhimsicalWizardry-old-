// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "DynamicCamera.generated.h"

UCLASS()
class WHIMSICALWIZARDRY_API ADynamicCamera : public ACameraActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camewra, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CameraSphere;

public:
	ADynamicCamera();

	void GetAllWizards();

	UFUNCTION(Server, Reliable)
		void Server_GetAllWizards();



protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	FVector FindAverageLocation();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetDynamicCamera() const { return GetCameraComponent(); }

	UPROPERTY(Replicated)
		TArray<class AActor*> WizardList;

};
