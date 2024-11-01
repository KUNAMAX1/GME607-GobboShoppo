// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Product.h"
#include "ProductShelf.generated.h"

UCLASS()
class GOBBOSHOPSIM_API AProductShelf : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductShelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* ShelfMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* ShelfMat;

	FVector SpawnLoc;
	FRotator SpawnRot;
	FActorSpawnParameters SpawnParams;


	AProduct* ProductsOnDisplay[8];

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};