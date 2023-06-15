// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

// Sets default values
AGhost::AGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SceneComponentの作成
	this->DefaultSceneRoot= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
//RootComponentにSceneComponentを設定
	RootComponent = this->DefaultSceneRoot;
	//SkeltalmeshComponentの作成
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeltalMeshComponent"));
	//SkeltalMeshをLoadしてSkeltalMeshComponentに設定
	USkeletalMesh* Mesh= LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/MannequinsXR/Meshs"));
    SkeletalMesh->SetSkeletalMesh(Mesh);

	//SkeltalMeshComponentをRootComponentにAttach
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

