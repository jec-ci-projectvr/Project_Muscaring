// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePoint.h"

// Sets default values
AMovePoint::AMovePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = defaultSceneRoot;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Sphere"), NULL, LOAD_None, NULL);
	staticMesh->SetStaticMesh(Mesh);

	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Engine/BasicShapes/BasicShapeMaterial"), NULL, LOAD_None, NULL);
	staticMesh->SetMaterial(0, Material);

	staticMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

	staticMesh->SetupAttachment(RootComponent);

	staticMesh->SetCanEverAffectNavigation(false);

	this->SetActorHiddenInGame(true);

	arrivalDistance = 100.0f;

	isActive = false;

	rotate = true;
}

// Called when the game starts or when spawned
void AMovePoint::BeginPlay()
{
	auto gameInst = GetWorld()->GetGameInstance();
	auto movePointSub = gameInst->GetSubsystem<UMovePointManagerSubSystem>();
	movePointSub->AddMovePoint(this);

	if (targetActor == nullptr) {
		targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}

	Super::BeginPlay();
}

// Called every frame
void AMovePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isActive) return;
	if (!CheckDistance()) return;

	this->Arrival();

	//一時停止ポイントの場合、再開トリガーが発動しているか確認
	if (waitPoint) {
		if (!CheckResumeTrigger()) return;
	}

	this->Departure();
}

void AMovePoint::Arrival()
{
	if (isArrived) return;
	isArrived = true;
	OnPointArrival.Broadcast(this);
}

void AMovePoint::Departure()
{
	OnPointDeparture.Broadcast(this, nextPoint);
	this->Destroy();
}

bool AMovePoint::CheckDistance()
{
	if (!IsValid(targetActor)) return false;
	if (GetDistanceTo(targetActor) > arrivalDistance) return false;

	return true;
}

bool AMovePoint::CheckResumeTrigger()
{
	if (!IsValid(resumeTriggerObject)) return true;
	if (!IMoveResumeTrigger::Execute_IsResumeTrigger(resumeTriggerObject)) return false;

	return true;
}

