// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

//Forward declarations to NOT include .h files and compile times to be faster
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UInputAction* InputMoveForward;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UInputAction* InputMoveBackwards;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UInputAction* InputMoveRight;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UInputAction* InputMoveLeft;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UInputAction* MouseLook;

	/*Movement Functions*/
	void MoveFwd(const FInputActionValue& Value);
	void MoveBckwd(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	/*Multiplies the looking around of the camera*/
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookBaseRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
