// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Product.h"
#include "FrogspawnProduct.h"
#include "MushroomProduct.h"
#include "FortniteProduct.h"
#include "NoMansSkyProduct.h"
#include "ProductEnum.h"
#include "ProductPassing.h"
#include "OuterWildsProduct.h"
#include "ProductBox.generated.h"

UCLASS()
class GOBBOSHOPSIM_API AProductBox : public AActor, public IProductPassing
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProductBox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
		EProductList CurrentProduct;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* BoxMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* BoxMat;

	FVector SpawnLoc;
	FRotator SpawnRot;
	FActorSpawnParameters SpawnParams;



	AProduct* ProductsOnDisplay[8];
	int CurrentTotal; 

	void SpawnItems();



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual AProduct* GetProduct() override;
	virtual void SetProduct(AProduct* product) override;

	void ResetProductPositions();

	//Github Test
};
