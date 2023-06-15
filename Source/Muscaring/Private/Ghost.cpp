// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

// Sets default values
AGhost::AGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SceneComponent‚Ìì¬
	this->DefaultSceneRoot= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
//RootComponent‚ÉSceneComponent‚ğİ’è
	RootComponent = this->DefaultSceneRoot;
	//SkeltalmeshComponent‚Ìì¬
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeltalMeshComponent"));
	//SkeltalMesh‚ğLoad‚µ‚ÄSkeltalMeshComponent‚Éİ’è
	USkeletalMesh* Mesh= LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/MannequinsXR/Meshs"));
    SkeletalMesh->SetSkeletalMesh(Mesh);

	//SkeltalMeshComponent‚ğRootComponent‚ÉAttach
	SkeletalMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

