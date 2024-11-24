// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldBarrel.generated.h"

UCLASS()
class GOBBOSHOPSIM_API AGoldBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoldBarrel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* BarrelMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
		int TotalGoldEarned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddGoldToBarrel(int AddGold);

};
