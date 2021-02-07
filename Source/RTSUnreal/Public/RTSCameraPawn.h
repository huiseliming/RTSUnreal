// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

UCLASS()
class RTSUNREAL_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSCameraPawn();


	// Components Variable
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RTSCameraPawn")
	class UStaticMeshComponent* Sphere = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RTSCameraPawn", meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RTSCameraPawn", meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RTSCameraPawn", meta=(AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* FloatingPawn;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Move
	UFUNCTION(BlueprintCallable,Category="RTSCameraPawn|Move")
	void AxisInputMoveForward(float Value);
	UFUNCTION(BlueprintCallable,Category="RTSCameraPawn|Move")
	void AxisInputMoveRight(float Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Move")
	float MoveSpeed = 1.0f;
	// Edge Move
	UPROPERTY(EditAnywhere, Category="ARTSPlayerController")
	float EdgeMoveWidthMultiplier = 10.f;
	
	//Rotate
	UFUNCTION(BlueprintCallable,Category="RTSCameraPawn|Rotate")
	void ActionInputPressedRotate();
	UFUNCTION(BlueprintCallable,Category="RTSCameraPawn|Rotate")
	void ActionInputReleasedRotate();
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Rotate")
	float RotatePitchSpeed = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Rotate")
	float RotateYawSpeed = 3.0f;
private:
	bool bRotateEnableFlag = false;
	
public:
	
	// Zoom
	UFUNCTION(BlueprintCallable,Category="RTSCameraPawn|Zoom")
	void AxisInputZoom(float Value);
	UFUNCTION(BlueprintCallable,Category="RTSCameraPawn|Zoom")
    void ActionInputPressedZoomReset();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Zoom")
	float DefaultZoomValue = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Zoom")
	float ZoomMinLimit = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Zoom")
	float ZoomMaxLimit = 3000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Zoom")
	float ZoomSpeed = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="RTSCameraPawn|Zoom")
	float TargetArmLengthLagSpeed = 10.f;
private:
	float TargetArmLengthValue = 0.0f;
};
