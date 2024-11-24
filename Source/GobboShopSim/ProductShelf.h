// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductPassing.h"
#include "Product.h"
#include "NoMansSkyProduct.h"
#include "FortniteProduct.h"
#include "OuterWildsProduct.h"
#include "ProductShelf.generated.h"

constexpr int NO_OF_PRODUCTS = 8;

UCLASS()
class GOBBOSHOPSIM_API AProductShelf : public AActor, public IProductPassing
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductShelf();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
		EProductList CurrentProduct;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* ShelfMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* ShelfMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* ShelfClothMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* ShelfClothMat;

	FVector SpawnLoc;
	FRotator SpawnRot;
	FActorSpawnParameters SpawnParams;

	int CurrentProductIndex;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual AProduct* GetProduct() override;
	virtual void SetProduct(AProduct* product) override;

	void ResetProductPositions();

	AProduct* ProductsOnDisplay[NO_OF_PRODUCTS];

	void ProductTaken(int ProductIndex);

};
