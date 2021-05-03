// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Components/TimelineComponent.h"
#include "Blueprint/UserWidget.h"
#include "Runner.generated.h"

UCLASS()
class SKYRUNNER_API ARunner : public ACharacter
{
	GENERATED_BODY()

		UTimelineComponent* MyTimeline;

public:
	// Sets default values for this character's properties
	ARunner();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GoRight();
	void GoLeft();



	void PauseGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaneData")
		int32 Lane=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaneData")
		int32 NewLane;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaneData")
		TArray<float> LaneY;

	int32 Score=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool MagnetActive=false;



public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* fCurve;
	UPROPERTY()
		float StartLocation;
	UPROPERTY()
		float EndLocation;
	UPROPERTY()
		FVector Loc;


	FOnTimelineFloat InterepFunction{};
	FOnTimelineEvent TimelineFinished{};

	UFUNCTION()
		void TimelineFloatReturn(float value);
	UFUNCTION()
		void OnTimelineFinished();

	UFUNCTION(BlueprintCallable)
		void DeathFunction();

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> PlayerWidgetClass;

	UUserWidget* PlayerWidget;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	UUserWidget* GameOverWidget;

};
