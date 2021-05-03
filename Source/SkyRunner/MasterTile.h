// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "MasterTile.generated.h"

UCLASS()
class SKYRUNNER_API AMasterTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* SpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* Box;




public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* Lane0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* Lane1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* Lane2;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Tile;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BoxPawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> CoinPawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MagnetPawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BootPawn;

	UFUNCTION(BlueprintCallable, Category = "ObstaclesFunc")
		void SpawnObstacles();

	float Rand;
	FVector trans;
	FRotator Rot;


};
