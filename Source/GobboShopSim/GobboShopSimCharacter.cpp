// Copyright Epic Games, Inc. All Rights Reserved.

#include "GobboShopSimCharacter.h"
#include "GobboShopSimProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ProductEnum.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include <DrawDebugHelpers.h>

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AGobboShopSimCharacter

AGobboShopSimCharacter::AGobboShopSimCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	/* Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	*/
}

void AGobboShopSimCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	
	PlayerProduct = (AProduct*)GetWorld()->SpawnActor(AProduct::StaticClass(), &ProductSpawnLoc, &ProductSpawnRot, ProductSpawnParams);
	
}


//////////////////////////////////////////////////////////////////////////
// Input

void AGobboShopSimCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGobboShopSimCharacter::OnClick);

	


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AGobboShopSimCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGobboShopSimCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGobboShopSimCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGobboShopSimCharacter::LookUpAtRate);
}

void AGobboShopSimCharacter::SetProduct(AProduct* product)
{
	PlayerProduct = product;
}

AProduct* AGobboShopSimCharacter::GetProduct()
{
	return PlayerProduct;
}

void AGobboShopSimCharacter::LineTraceForward()
{
	FVector PlayerLoc;
	FRotator PlayerRot;
	FHitResult Hit;

	

	GetController()->GetPlayerViewPoint(PlayerLoc, PlayerRot);

	FVector Start = PlayerLoc;
	FVector End = Start + (PlayerRot.Vector() * PlayerReach);

	FCollisionQueryParams TraceParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);

	if (bHit)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("You Hit %s"), *Hit.GetActor()->GetName()));

		DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 2.0f);

		if (Hit.GetActor()->GetClass()->ImplementsInterface(UProductPassing::StaticClass()))
		{
			AProduct* TempProduct;
			TempProduct = PlayerProduct;
			PlayerProduct = Cast<IProductPassing>(Hit.GetActor())->GetProduct();
			Cast<IProductPassing>(Hit.GetActor())->SetProduct(TempProduct);
		}

	}
}

void AGobboShopSimCharacter::OnClick()
{
	LineTraceForward();
}





void AGobboShopSimCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGobboShopSimCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGobboShopSimCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGobboShopSimCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGobboShopSimCharacter::Tick(float DeltaTime)
{
	if (GEngine && PlayerProduct)
	{
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Green, PlayerProduct->GetLabel());
	}

	PlayerProduct->SetActorLocation(this->GetActorLocation() + FVector(100, 5, 5));
}


