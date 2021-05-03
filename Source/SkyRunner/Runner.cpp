// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "Runner_GameMode.h"

// Sets default values
ARunner::ARunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	
	LaneY.Add(-330.f);
	LaneY.Add(0.0f);
	LaneY.Add(320.f);

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	InterepFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerWidgetClass) {
		PlayerWidget = CreateWidget(GetWorld(), PlayerWidgetClass);
		PlayerWidget->AddToViewport();
	}
	
}


// Called every frame
void ARunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction);


}

// Called to bind functionality to input
void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("GoRight", IE_Pressed, this, &ARunner::GoRight);
	PlayerInputComponent->BindAction("GoLeft", IE_Pressed, this, &ARunner::GoLeft);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);


}

void ARunner::GoRight()
{
	NewLane = FMath::Clamp(Lane+1 , 0, 2);
	if (fCurve) {
		MyTimeline->AddInterpFloat(fCurve, InterepFunction, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(TimelineFinished);
		StartLocation = LaneY[Lane];
		EndLocation = LaneY[NewLane];

		MyTimeline->SetLooping(false);
		//MyTimeline->SetIgnoreTimeDilation(true);

		MyTimeline->PlayFromStart();
	}
}
void ARunner::GoLeft()
{
	NewLane = FMath::Clamp(Lane - 1, 0, 2);
	if (fCurve) {
		MyTimeline->AddInterpFloat(fCurve, InterepFunction, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(TimelineFinished);
		StartLocation = LaneY[Lane];
		EndLocation = LaneY[NewLane];

		MyTimeline->SetLooping(false);
		//MyTimeline->SetIgnoreTimeDilation(true);

		MyTimeline->PlayFromStart();
	}
}


void ARunner::TimelineFloatReturn(float value)
{
	float YLocation = FMath::Lerp(StartLocation, EndLocation, value);
	Loc = GetActorLocation();

	SetActorLocation(FVector(Loc.X, YLocation, Loc.Z));
}

void ARunner::OnTimelineFinished()
{
	Lane = NewLane;
	
}


void ARunner::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
void ARunner::DeathFunction()
{

	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();
	//FTimerHandle UnusedHandle;
	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunner::PauseGame, 3.0f, false);

	if (GameOverWidgetClass) {
		GameOverWidget = CreateWidget(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
	}

	ARunner_GameMode* Obj = Cast<ARunner_GameMode>(GetWorld()->GetAuthGameMode());
	if (Obj) {
		Score = Obj->CurrentPoints;
	}
	bool Saved = UGameplayStatics::DoesSaveGameExist(TEXT("MySlot"), 0);
	if (Saved) {
		UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("MySlot", 0));
		if (Score > SaveGameInstance->HighScore) {
			SaveGameInstance->HighScore = Score;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
		}


	}
	else {
		UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		SaveGameInstance->HighScore = Score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
	}



	
}
