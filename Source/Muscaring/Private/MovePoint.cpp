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

	arrivalDistance = 100.0f;
}

// Called when the game starts or when spawned
void AMovePoint::BeginPlay()
{
	if (!displayMesh) staticMesh->DestroyComponent();

	if (targetActor == nullptr)
	{
		targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}

	Super::BeginPlay();
}

// Called every frame
void AMovePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (targetDistination != this) return;
	if (GetDistanceTo(targetActor) > arrivalDistance) return;
	
	OnPointArrival.Broadcast(this);

	if (waitPoint && IsValid(resumeTriggerObject))
	{
		if (!IMoveResumeTrigger::Execute_IsResumeTrigger(resumeTriggerObject)) return;

		OnPointDeparture.Broadcast(this, nextPoint);
		this->Destroy();
		return;
	}
	else {
		OnPointDeparture.Broadcast(this, nextPoint);
		this->Destroy();
	}
}

