// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComponent);

	LookBaseRate = 50;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ASCharacter::MoveFwd);
	enhancedInputComponent->BindAction(InputMoveBackwards, ETriggerEvent::Triggered, this, &ASCharacter::MoveBckwd);
	enhancedInputComponent->BindAction(MouseLook, ETriggerEvent::Triggered, this, &ASCharacter::Look);
}

/*Movement and look around functions*/
void ASCharacter::MoveFwd(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveVector.X);
}
void ASCharacter::MoveBckwd(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveVector.X);
}
void ASCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X * LookBaseRate * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(LookVector.Y * LookBaseRate * GetWorld()->GetDeltaSeconds());
}