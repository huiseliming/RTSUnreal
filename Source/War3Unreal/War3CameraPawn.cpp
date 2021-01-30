// Fill out your copyright notice in the Description page of Project Settings.


#include "War3CameraPawn.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AWar3CameraPawn::AWar3CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create SceneComponent as RootComponent 
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere")); 
	Sphere->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Sphere->SetStaticMesh(SphereMeshAsset.Object);
	Sphere->SetRelativeRotation(FRotator(-70.f,0.f,0.f));
	Sphere->SetRelativeScale3D(FVector(0.25f,0.25f,0.25f));
	
	// Create SpringArmComponent attach to RootComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Sphere);
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->bDoCollisionTest = false;
	// Create CameraComponent attach to SpringArmComponent
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawn = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawn"));
	
	// |-SceneComponent
	//   |-SpringArmComponent
	//	   |-CameraComponent
}

// Called when the game starts or when spawned
void AWar3CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	SpringArm->TargetArmLength = DefaultZoomValue;
}

// Called every frame
void AWar3CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWar3CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// BindAction
	PlayerInputComponent->BindAction(TEXT("ZoomReset"), EInputEvent::IE_Pressed,this,&AWar3CameraPawn::ZoomReset);
	// BindAxis 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWar3CameraPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AWar3CameraPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AWar3CameraPawn::Zoom);
}

void AWar3CameraPawn::MoveForward(float Value)
{
	FloatingPawn->AddInputVector(FVector(Value,0.f,0.f));
}

void AWar3CameraPawn::MoveRight(float Value)
{
	FloatingPawn->AddInputVector(FVector(0.f,Value,0.f));	
}

void AWar3CameraPawn::Zoom(float Value)
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + Value * ZoomSpeed,ZoomMinLimit,ZoomMaxLimit);
}

void AWar3CameraPawn::ZoomReset()
{
	SpringArm->TargetArmLength = DefaultZoomValue;
}
