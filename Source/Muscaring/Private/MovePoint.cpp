// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePoint.h"

// Sets default values
AMovePoint::AMovePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot_ = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = defaultSceneRoot_;

	staticMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Sphere"), NULL, LOAD_None, NULL);
	staticMesh_->SetStaticMesh(Mesh);

	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Engine/BasicShapes/BasicShapeMaterial"), NULL, LOAD_None, NULL);
	staticMesh_->SetMaterial(0, Material);

	staticMesh_->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

	staticMesh_->SetupAttachment(RootComponent);

	staticMesh_->SetCanEverAffectNavigation(false);

	this->SetActorHiddenInGame(true);

	arrivalDistance_ = 100.0f;

	isActive_ = false;

	rotate_ = true;
}

// Called when the game starts or when spawned
void AMovePoint::BeginPlay()
{
	if (targetActor_ == nullptr) {
		targetActor_ = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}

	Super::BeginPlay();
}

// Called every frame
void AMovePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isActive_) return;
	if (!CheckDistance()) return;

	this->Arrival();

	//一時停止ポイントの場合、再開トリガーが発動しているか確認
	if (waitPoint_) {
		if (!CheckResumeTrigger()) return;
	}

	this->Departure();
}

void AMovePoint::Arrival()
{
	if (isArrived_) return;
	isArrived_ = true;
	OnPointArrival.Broadcast(this);
}

void AMovePoint::Departure()
{
	OnPointDeparture.Broadcast(this, nextPoint_);
	this->Destroy();
}

bool AMovePoint::CheckDistance()
{
	if (!IsValid(targetActor_)) return false;
	if (GetDistanceTo(targetActor_) > arrivalDistance_) return false;

	return true;
}

bool AMovePoint::CheckResumeTrigger()
{
	if (!IsValid(resumeTriggerObject_)) return true; //再開トリガーが設定されていない場合は常にtrue
	if (!resumeTriggerObject_->Implements<UMoveResumeTrigger>()) return true; //IMoveResumeTriggerを実装していない場合は常にtrue
	if (!IMoveResumeTrigger::Execute_IsResumeTrigger(resumeTriggerObject_)) return false;

	return true;
}
