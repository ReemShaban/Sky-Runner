// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Runner_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SKYRUNNER_API ARunner_GameMode : public AGameMode
{
	GENERATED_BODY()

	ARunner_GameMode();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int32 CurrentPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int32 PointsMultiplier=15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
		int32 Coins;

};

