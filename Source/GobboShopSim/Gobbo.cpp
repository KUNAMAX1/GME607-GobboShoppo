// Fill out your copyright notice in the Description page of Project Settings.


#include "Gobbo.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AGobbo::AGobbo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GobboMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gobbo Mesh"));

	GobboMat = CreateDefaultSubobject<UMaterial>(TEXT("Gobbo Mat"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>GobboCheck(TEXT("/Game/Goblin/Goblin2"));

	static ConstructorHelpers::FObjectFinder<UMaterial>GobboMatCheck(TEXT("/Game/Goblin/M_Goblin"));

	if (GobboCheck.Succeeded())
	{
		GobboMesh->SetSkeletalMesh(GobboCheck.Object);
	}
	if (GobboMatCheck.Succeeded())
	{
		GobboMat = GobboMatCheck.Object;

		GobboMesh->SetMaterial(0, GobboMat);
	}

	GobboMesh->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);

	GobboGenerateShoppingList();
	GobboState = EGobboState::CHECKLIST;

	GobboShoppingSpeed = 1;
	ProductCost = 0;
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

	
}

// Called every frame
void AGobbo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateGobbo(DeltaTime);
}

void AGobbo::SetGobboSeenShelves(TArray<AProductShelf*> NewShelves)
{
	GobboSeenShelves = NewShelves;
}

void AGobbo::SetGobboShoppingTarget(AActor* NewTarget)
{
	GobboShoppingTarget = NewTarget;
}

void AGobbo::SetPayPoint(AGoldBarrel* GoldBarrel)
{
	PayPoint = GoldBarrel;
}

void AGobbo::GobboBrowsing(float DeltaTime)
{

	if (FVector::Dist(this->GetActorLocation(), GobboShoppingTarget->GetActorLocation()) < 200)
	{
		AProductShelf* ShelfNearGobbo = Cast<AProductShelf>(GobboShoppingTarget);

		for (int i = 0; i < MAX_SHOPPING_LIST; i++)
		{
			if (GobboShoppingList.bCompletedPurchase[i] == false)
			{
				for (int j = 0; j < 8; j++)
				{
					if (ShelfNearGobbo->ProductsOnDisplay[j]->GetEnum() == GobboShoppingList.WantedProduct[i])
					{
						GobboShoppingList.bCompletedPurchase[i] = true;
						ProductCost += ShelfNearGobbo->ProductsOnDisplay[j]->GetProductPrice();
						ShelfNearGobbo->ProductTaken(j);
						break;
					}
				}

				GobboState = EGobboState::CHECKLIST;
			}
		}

		
	}
	else
	{
		GobboGoTo(DeltaTime);
	}

}

void AGobbo::GobboExit()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, TEXT("I DONE SHOPPING"));
	this->Destroy();
}

void AGobbo::GobboPay(float DeltaTime)
{
	GobboShoppingTarget = PayPoint;

	if (FVector::Dist(this->GetActorLocation(), GobboShoppingTarget->GetActorLocation()) < 100)
	{
		PayPoint->AddGoldToBarrel(ProductCost);
		GobboState = EGobboState::EXIT;
	}
	else
	{
		GobboGoTo(DeltaTime);
	}

}

void AGobbo::PrintGobboSeenShelves()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(9, 2.f, FColor::Magenta, FString::Printf(TEXT("I can see %d Shelves"), GobboSeenShelves.Num()));
}

void AGobbo::UpdateGobbo(float DeltaTime)
{

	if (GobboShoppingTarget)
	{
		FRotator GobboLook = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), GobboShoppingTarget->GetActorLocation());

		this->SetActorRotation(GobboLook + FRotator(0, -90, 0));
	}
	FVector TextLocation = this->GetActorLocation();

	TextLocation.Z += 180.f;

	TextRenderComponent->SetRelativeLocation(TextLocation);
	TextRenderComponent->SetRelativeRotation(this->GetActorRotation()+ FRotator(0, 90, 0));
	

	switch (GobboState)
	{
	case EGobboState::BROWSING:
		GobboBrowsing(DeltaTime);
		break;

	case EGobboState::CHECKLIST:
		GobboCheckList();
		break;

	case EGobboState::PAY:
		GobboPay(DeltaTime);
		break;

	case EGobboState::EXIT:
		GobboExit();
		break;

	}
}

void AGobbo::GobboGoTo(float DeltaTime)
{
	//SetActorRotation(FRotationMatrix::MakeFromX(GobboShoppingTarget->GetActorLocation() + this->GetActorLocation()).Rotator());

	if (GobboShoppingTarget)
	{


		FVector Start = this->GetActorLocation();
		FVector End = GobboShoppingTarget->GetActorLocation();


		FVector MoveLocation = FMath::VInterpTo(Start, End, DeltaTime, GobboShoppingSpeed);

		this->SetActorLocation(MoveLocation);

	}
}

void AGobbo::GobboGenerateShoppingList()
{
	for (int i = 0; i < MAX_SHOPPING_LIST; i++)
	{
		GobboShoppingList.InBag[i] = EProductList::EMPTY;
		GobboShoppingList.bCompletedPurchase[i] = false;

		int RandomShoppingItems = FMath::RandRange(0, 3);

		switch (RandomShoppingItems)
		{
		case 0:
			GobboShoppingList.WantedProduct[i] = EProductList::EMPTY;
			break;

		case 1:
			GobboShoppingList.WantedProduct[i] = EProductList::FORTNITE;
			break;

		case 2:
			GobboShoppingList.WantedProduct[i] = EProductList::NOMANSSKY;
			break;

		case 3:
			GobboShoppingList.WantedProduct[i] = EProductList::OUTERWILDS;
			break;

		}
	}
}

void AGobbo::GobboCheckList()
{
	for (int i = 0; i < MAX_SHOPPING_LIST; i++)
	{
		if (GobboShoppingList.WantedProduct[i] == GobboShoppingList.InBag[i])
		{
			GobboShoppingList.bCompletedPurchase[i] = true;
		}
	}

	bool bCompletedAllItems = true;

	for (int i = 0; i < MAX_SHOPPING_LIST; i++)
	{
		if (GobboShoppingList.bCompletedPurchase[i] == false)
		{
			bCompletedAllItems = false;
		}
	}

	if (bCompletedAllItems == true)
	{
		GobboState = EGobboState::PAY;
	}
	else 
	{
		GobboShoppingTarget = GobboSeenShelves[FMath::RandRange(0, GobboSeenShelves.Num() - 1)];
		GobboState = EGobboState::BROWSING;
	}

}


