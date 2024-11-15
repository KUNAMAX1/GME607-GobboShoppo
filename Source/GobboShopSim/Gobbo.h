// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductShelf.h"
#include "Gobbo.generated.h"

UCLASS()
class GOBBOSHOPSIM_API AGobbo : public AActor
{
	GENERATED_BODY() //GitHub Check

public:
	// Sets default values for this actor's properties
	AGobbo();
	AGobbo(TArray<AActor*> _GobboSeenShelves);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeadText")
		class UTextRenderComponent* TextRenderComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* GobboMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UMaterial* GobboMat;

	TArray<AActor*> GobboSeenShelves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gobbo Settings")
		float GobboShoppingSpeed = 3;

	bool bIsMoving;

	AActor* GobboShoppingTarget;

	void GobboGoTo(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SetGobboSeenShelves(TArray<AActor*> NewShelves);
	void SetGobboShoppingTarget(AActor* NewTarget);

	void TempMoveSyst();

	void PrintGobboSeenShelves();
	

};
