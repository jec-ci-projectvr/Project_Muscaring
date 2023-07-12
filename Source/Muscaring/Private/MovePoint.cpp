// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePoint.h"

// Sets default values
AMovePoint::AMovePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Sphere"), NULL, LOAD_None, NULL);
	StaticMesh->SetStaticMesh(Mesh);

	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Engine/BasicShapes/BasicShapeMaterial"), NULL, LOAD_None, NULL);
	StaticMesh->SetMaterial(0, Material);

	StaticMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

	StaticMesh->SetupAttachment(RootComponent);

	arrivalDistance = 10.0f;
}

// Called when the game starts or when spawned
void AMovePoint::BeginPlay()
{
	if (targetActor == nullptr)
	{
		targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}

	Super::BeginPlay();
}

// Called every frame
void AMovePoint::Tick(float DeltaTime)
{
	if (GetHorizontalDistanceTo(targetActor) < arrivalDistance && targetDistination == this) {
		OnPointArrival.Broadcast(this, nextPoint);
	}

	Super::Tick(DeltaTime);
}

