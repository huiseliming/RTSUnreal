// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraPawn.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARTSCameraPawn::ARTSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create SceneComponent as RootComponent
	
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere")); 
	RootComponent = Sphere;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Sphere->SetStaticMesh(SphereMeshAsset.Object);
	Sphere->SetRelativeRotation(FRotator(-70.f,0.f,0.f));
	Sphere->SetRelativeScale3D(FVector(0.25f,0.25f,0.25f));
	
	// Create SpringArmComponent attach to RootComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Sphere);
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	// Create CameraComponent attach to SpringArmComponent
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawn = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawn"));
	
	// |-SphereComponent
	//   |-SpringArmComponent
	//	   |-CameraComponent
}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	SpringArm->TargetArmLength = DefaultZoomValue;
	TargetArmLengthValue = SpringArm->TargetArmLength;
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetArmLengthValue, DeltaTime, TargetArmLengthLagSpeed);
	if (bRotateEnableFlag)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
		float MouseDeltaX,MouseDeltaY;
		PlayerController->GetInputMouseDelta(MouseDeltaX,MouseDeltaY);
		FRotator Rotator = Sphere->GetComponentRotation();
		Sphere->SetRelativeRotation(FRotator(
			FMath::Clamp(Rotator.Pitch + MouseDeltaY * RotatePitchSpeed,-70.f,0.f),
			Rotator.Yaw + MouseDeltaX * RotateYawSpeed,
			0.f));
	}
	//
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		int32 ViewportSizeX,ViewportSizeY;
		float MouseLocationX,MouseLocationY;
		PlayerController->GetViewportSize(ViewportSizeX,ViewportSizeY);
		if (ViewportSizeX != 0 && PlayerController->GetMousePosition(MouseLocationX,MouseLocationY))
		{
			//GLog->Log(FString::Printf(TEXT("%d, %d, %f, %f"),  ViewportSizeX, ViewportSizeY, MouseLocationX, MouseLocationY));
			const float Viewport1KBase = FMath::Min(ViewportSizeY,ViewportSizeY) / 1080.f;
			const float EdgeMoveWidth = EdgeMoveWidthMultiplier * Viewport1KBase;
			if (MouseLocationX + EdgeMoveWidth >= ViewportSizeX)
			{
				AxisInputMoveRight(	(EdgeMoveWidth - (ViewportSizeX - MouseLocationX)) / EdgeMoveWidth);
			}
			if (MouseLocationX - EdgeMoveWidth <= 0.f)
			{
				AxisInputMoveRight((- EdgeMoveWidth - MouseLocationX) / EdgeMoveWidth);
			}
			if (MouseLocationY + EdgeMoveWidth >= ViewportSizeY)
			{
				AxisInputMoveForward(-(EdgeMoveWidth - (ViewportSizeY - MouseLocationY)) / EdgeMoveWidth);
			}
			if (MouseLocationY - EdgeMoveWidth <= 0.f)
			{
				AxisInputMoveForward((EdgeMoveWidth - MouseLocationY) / EdgeMoveWidth);
			}
		}
	}
}

// Called to bind functionality to input
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// BindAction
	PlayerInputComponent->BindAction(TEXT("Rotate"), EInputEvent::IE_Pressed, this, &ARTSCameraPawn::ActionInputPressedRotate);
	PlayerInputComponent->BindAction(TEXT("Rotate"), EInputEvent::IE_Released, this, &ARTSCameraPawn::ActionInputReleasedRotate);
	PlayerInputComponent->BindAction(TEXT("ZoomReset"), EInputEvent::IE_Pressed,this, &ARTSCameraPawn::ActionInputPressedZoomReset);
	// BindAxis 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARTSCameraPawn::AxisInputMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARTSCameraPawn::AxisInputMoveRight);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &ARTSCameraPawn::AxisInputZoom);
}

void ARTSCameraPawn::AxisInputMoveForward(float Value)
{
	FloatingPawn->AddInputVector(FVector::VectorPlaneProject(GetActorForwardVector(),FVector::UpVector).GetUnsafeNormal() * Value * MoveSpeed);
}

void ARTSCameraPawn::AxisInputMoveRight(float Value)
{
	FloatingPawn->AddInputVector(FVector::VectorPlaneProject(GetActorRightVector(),FVector::UpVector).GetUnsafeNormal() * Value * MoveSpeed);	
}

void ARTSCameraPawn::ActionInputPressedRotate()
{
	bRotateEnableFlag = true;
}

void ARTSCameraPawn::ActionInputReleasedRotate()
{
	bRotateEnableFlag = false;
}

void ARTSCameraPawn::AxisInputZoom(float Value)
{
	TargetArmLengthValue = FMath::Clamp(TargetArmLengthValue + Value * ZoomSpeed,ZoomMinLimit,ZoomMaxLimit);
}

void ARTSCameraPawn::ActionInputPressedZoomReset()
{
	TargetArmLengthValue = DefaultZoomValue;
}
