// Fill out your copyright notice in the Description page of Project Settings.


#include "War3CameraPawn.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWar3CameraPawn::AWar3CameraPawn()
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
void AWar3CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	SpringArm->TargetArmLength = DefaultZoomValue;
	TargetArmLengthValue = SpringArm->TargetArmLength;
}

// Called every frame
void AWar3CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
}

// Called to bind functionality to input
void AWar3CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// BindAction
	PlayerInputComponent->BindAction(TEXT("Rotate"), EInputEvent::IE_Pressed, this, &AWar3CameraPawn::ActionInputPressedRotate);
	PlayerInputComponent->BindAction(TEXT("Rotate"), EInputEvent::IE_Released, this, &AWar3CameraPawn::ActionInputReleasedRotate);
	PlayerInputComponent->BindAction(TEXT("ZoomReset"), EInputEvent::IE_Pressed,this, &AWar3CameraPawn::ActionInputPressedZoomReset);
	// BindAxis 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWar3CameraPawn::AxisInputMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AWar3CameraPawn::AxisInputMoveRight);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AWar3CameraPawn::AxisInputZoom);
}

void AWar3CameraPawn::AxisInputMoveForward(float Value)
{
	FloatingPawn->AddInputVector(FVector::VectorPlaneProject(GetActorForwardVector(),FVector::UpVector).GetUnsafeNormal() * Value * MoveSpeed);
}

void AWar3CameraPawn::AxisInputMoveRight(float Value)
{
	FloatingPawn->AddInputVector(FVector::VectorPlaneProject(GetActorRightVector(),FVector::UpVector).GetUnsafeNormal() * Value * MoveSpeed);	
}

void AWar3CameraPawn::ActionInputPressedRotate()
{
	bRotateEnableFlag = true;
}

void AWar3CameraPawn::ActionInputReleasedRotate()
{
	bRotateEnableFlag = false;
}

void AWar3CameraPawn::AxisInputZoom(float Value)
{
	TargetArmLengthValue = FMath::Clamp(TargetArmLengthValue + Value * ZoomSpeed,ZoomMinLimit,ZoomMaxLimit);
}

void AWar3CameraPawn::ActionInputPressedZoomReset()
{
	TargetArmLengthValue = DefaultZoomValue;
}
