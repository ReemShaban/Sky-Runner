// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterTile.h"

// Sets default values
AMasterTile::AMasterTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	StaticMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	StaticMesh->SetRelativeScale3D(FVector(10.f, 10.f, 0.1f));

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	SpawnPoint->SetupAttachment(StaticMesh);
	SpawnPoint->SetRelativeLocation(FVector(0.0f, -50.0f, 0.0f));
	SpawnPoint->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpawnPoint->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));


	Box = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	Box->SetupAttachment(SpawnPoint);
	Box->SetRelativeLocation(FVector(-4.0f, 0.0f, 6600.0f));
	Box->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Box->SetRelativeScale3D(FVector(0.4f, 2.f, 200.f));

	Lane0 = CreateDefaultSubobject<UArrowComponent>("LaneZeroComponent");
	Lane0->SetupAttachment(RootComponent);
	Lane0->SetRelativeLocation(FVector(0.0f, -330.0f, 0.0f));
	Lane0->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Lane0->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	Lane1 = CreateDefaultSubobject<UArrowComponent>("LaneOneComponent");
	Lane1->SetupAttachment(RootComponent);
	Lane1->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Lane1->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Lane1->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	Lane2 = CreateDefaultSubobject<UArrowComponent>("LaneTwoComponent");
	Lane2->SetupAttachment(RootComponent);
	Lane2->SetRelativeLocation(FVector(0.0f, 320.0f, 0.0f));
	Lane2->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Lane2->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));



}

// Called when the game starts or when spawned
void AMasterTile::BeginPlay()
{
	Super::BeginPlay();
	//SpawnObstacles();
	
}

// Called every frame
void AMasterTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterTile::SpawnObstacles()
{
	Rand = FMath::RandRange(0.0f,1.3f);
	trans = Lane0->GetComponentLocation();
	Rot = FRotator(0.0f, 0.0f, 0.0f);
	if (Rand >= 0.0f && Rand < 0.33f) {
		GetWorld()->SpawnActor(Tile, &trans, &Rot);
	}
	else if(Rand >= 0.4f && Rand < 0.5f) {
		GetWorld()->SpawnActor(BoxPawn, &trans, &Rot);

	}
	else if (Rand >= 0.5f && Rand < 0.95f) {
		GetWorld()->SpawnActor(CoinPawn, &trans, &Rot);

	}
	else if (Rand >= 0.95f && Rand < 0.975f) {
		GetWorld()->SpawnActor(MagnetPawn, &trans, &Rot);

	}
	else if (Rand >= 0.975f && Rand < 1.0f) {
		GetWorld()->SpawnActor(BootPawn, &trans, &Rot);

	}
	Rand = FMath::RandRange(0.0f, 1.3f);
	trans = Lane1->GetComponentLocation();
	if (Rand >= 0.0f && Rand < 0.33f) {
		GetWorld()->SpawnActor(Tile, &trans, &Rot);
	}
	else if (Rand >= 0.4f && Rand < 0.5f) {
		GetWorld()->SpawnActor(BoxPawn, &trans, &Rot);

	}
	else if (Rand >= 0.5f && Rand < 0.95f) {
		GetWorld()->SpawnActor(CoinPawn, &trans, &Rot);

	}
	else if (Rand >= 0.95f && Rand < 0.975f) {
		GetWorld()->SpawnActor(MagnetPawn, &trans, &Rot);

	}
	else if (Rand >= 0.975f && Rand < 1.0f) {
		GetWorld()->SpawnActor(BootPawn, &trans, &Rot);

	}
	Rand = FMath::RandRange(0.0f, 1.3f);
	trans = Lane2->GetComponentLocation();
	if (Rand >= 0.0f && Rand < 0.33f) {
		GetWorld()->SpawnActor(Tile, &trans, &Rot);
	}
	else if (Rand >= 0.4f && Rand < 0.5f) {
		GetWorld()->SpawnActor(BoxPawn, &trans, &Rot);

	}
	else if (Rand >= 0.5f && Rand < 0.95f) {
		GetWorld()->SpawnActor(CoinPawn, &trans, &Rot);

	}
	else if (Rand >= 0.95f && Rand < 0.975f) {
		GetWorld()->SpawnActor(MagnetPawn, &trans, &Rot);

	}
	else if (Rand >= 0.975f && Rand < 1.0f) {
		GetWorld()->SpawnActor(BootPawn, &trans, &Rot);

	}
}

