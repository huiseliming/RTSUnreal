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
	class USceneComponent* Scene = nullptr;
	
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

	UFUNCTION(BlueprintCallable,Category="War3CameraPawn")
	void MoveForward(float Value);
	UFUNCTION(BlueprintCallable,Category="War3CameraPawn")
	void MoveRight(float Value);




	
};
