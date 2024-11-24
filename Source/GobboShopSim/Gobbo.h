// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductShelf.h"
#include "GoldBarrel.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gobbo.generated.h"

constexpr int MAX_SHOPPING_LIST = 4;

USTRUCT(BlueprintType)
struct FGobboShoppingList
{
	GENERATED_BODY()

	EProductList WantedProduct[MAX_SHOPPING_LIST];
	EProductList InBag[MAX_SHOPPING_LIST];
	bool bCompletedPurchase[MAX_SHOPPING_LIST];

};
UCLASS()
class GOBBOSHOPSIM_API AGobbo : public AActor
{
	GENERATED_BODY() //GitHub Check

		enum class EGobboState : int8
	{
		BROWSING,
		CHECKLIST,
		PAY,
		EXIT
	};

public:
	// Sets default values for this actor's properties
	AGobbo();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeadText")
		class UTextRenderComponent* TextRenderComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USkeletalMeshComponent* GobboMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* GobboMat;

	TArray<AProductShelf*> GobboSeenShelves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gobbo Settings")
		float GobboShoppingSpeed;

	bool bIsMoving;
	int ProductCost;

	AActor* GobboShoppingTarget;
	AGoldBarrel* PayPoint;

	void GobboGoTo(float DeltaTime);
	void GobboGenerateShoppingList();
	void GobboCheckList();
	void GobboBrowsing(float DeltaTime);
	void GobboExit();
	void GobboPay(float DeltaTime);



	FGobboShoppingList GobboShoppingList;
	EGobboState GobboState;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SetGobboSeenShelves(TArray<AProductShelf*> NewShelves);
	void SetGobboShoppingTarget(AActor* NewTarget);
	void SetPayPoint(AGoldBarrel* GoldBarrel);



	void PrintGobboSeenShelves();
	void UpdateGobbo(float DeltaTime);


};
