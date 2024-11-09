// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductShelf.h"
#include "Gobbo.h"
#include "EntranceDoor.generated.h"

UCLASS()
class GOBBOSHOPSIM_API AEntranceDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntranceDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* GobboMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* GobboMat;

	FVector SpawnLoc;
	FRotator SpawnRot;
	FActorSpawnParameters SpawnParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GobboSpawner")
		bool bGobboSpawner = true;

	int GobboSpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GobboSpawner")
		int GobboSpawnMult = 10;

	TArray<AActor*> CurrentShelfLayout;

	TArray<AGobbo*> GobboShoppers;

	void GobboSpawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
