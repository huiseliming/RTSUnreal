// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "War3CameraPawn.generated.h"

UCLASS()
class WAR3UNREAL_API AWar3CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWar3CameraPawn();


	// Components Variable
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="War3CameraPawn")
	class UStaticMeshComponent* Sphere = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="War3CameraPawn", meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="War3CameraPawn", meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="War3CameraPawn", meta=(AllowPrivateAccess = "true"))
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
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn|Move")
	void AxisInputMoveForward(float Value);
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn|Move")
	void AxisInputMoveRight(float Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Move")
	float MoveSpeed = 1.0f;
	
	//Rotate
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn|Rotate")
	void ActionInputPressedRotate();
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn|Rotate")
	void ActionInputReleasedRotate();
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Rotate")
	float RotatePitchSpeed = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Rotate")
	float RotateYawSpeed = 3.0f;
private:
	bool bRotateEnableFlag = false;
	
public:
	
	// Zoom
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn|Zoom")
	void AxisInputZoom(float Value);
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn|Zoom")
    void ActionInputPressedZoomReset();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Zoom")
	float DefaultZoomValue = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Zoom")
	float ZoomMinLimit = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Zoom")
	float ZoomMaxLimit = 3000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Zoom")
	float ZoomSpeed = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="War3CameraPawn|Zoom")
	float TargetArmLengthLagSpeed = 10.f;
private:
	float TargetArmLengthValue = 0.0f;
};
