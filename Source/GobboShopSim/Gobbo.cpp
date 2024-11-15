// Fill out your copyright notice in the Description page of Project Settings.


#include "Gobbo.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AGobbo::AGobbo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GobboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gobbo Mesh"));

	GobboMat = CreateDefaultSubobject<UMaterial>(TEXT("Gobbo Mat"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>GobboCheck(TEXT("/Game/Goblin/Goblin"));

	static ConstructorHelpers::FObjectFinder<UMaterial>GobboMatCheck(TEXT("/Game/Goblin/M_Goblin"));

	if (GobboCheck.Succeeded())
	{
		GobboMesh->SetStaticMesh(GobboCheck.Object);
	}
	if (GobboMatCheck.Succeeded())
	{
		GobboMat = GobboMatCheck.Object;

		GobboMesh->SetMaterial(0, GobboMat);
	}

	GobboMesh->SetRelativeScale3D(FVector(22, 22, 22));

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);

	

}

// Called when the game starts or when spawned
void AGobbo::BeginPlay()
{
	Super::BeginPlay();
	
	TextRenderComponent->SetText(TEXT("default text"));
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetVerticalAlignment(EVRTA_TextCenter);
	TextRenderComponent->SetWorldSize(25.0f);
	TextRenderComponent->SetVisibility(true);

	TextRenderComponent->SetRelativeLocation(FVector(-140, 300, 120));
	TextRenderComponent->SetRelativeRotation(FRotator(0, -90, 0));
	
}

// Called every frame
void AGobbo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempMoveSyst();

	GobboGoTo(DeltaTime);
}

AGobbo::AGobbo(TArray<AActor*> _GobboSeenShelves)
{
	GobboSeenShelves = _GobboSeenShelves;
}

void AGobbo::SetGobboSeenShelves(TArray<AActor*> NewShelves)
{
	GobboSeenShelves = NewShelves;
}

void AGobbo::SetGobboShoppingTarget(AActor* NewTarget)
{
	GobboShoppingTarget = NewTarget;
}

void AGobbo::TempMoveSyst()
{
	if (GobboSeenShelves.Num() > 0)
	{



		int ShelfPick = FMath::RandRange(0, (GobboSeenShelves.Num() - 1));

		GobboShoppingTarget = GobboSeenShelves[ShelfPick];
	}
}

void AGobbo::PrintGobboSeenShelves()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(9, 2.f, FColor::Magenta, FString::Printf(TEXT("I can see %d Shelves"), GobboSeenShelves.Num()));
}

void AGobbo::GobboGoTo(float DeltaTime)
{

	if (GobboShoppingTarget)
	{


		FVector Start = this->GetActorLocation();
		FVector End = GobboShoppingTarget->GetActorLocation();


		FVector MoveLocation = FMath::VInterpTo(Start, End, DeltaTime, GobboShoppingSpeed);

		this->SetActorLocation(MoveLocation);

	}
}

