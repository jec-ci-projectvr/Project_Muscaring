// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
AGhost::AGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SceneComponent�̍쐬
	this->DefaultSceneRoot= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
//RootComponent��SceneComponent��ݒ�
	RootComponent = this->DefaultSceneRoot;
	//SkeltalmeshComponent�̍쐬
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeltalMeshComponent"));
	//SkeltalMesh��Load����SkeltalMeshComponent�ɐݒ�
	USkeletalMesh* Mesh= LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/MannequinsXR/Meshs"));
    SkeletalMesh->SetSkeletalMesh(Mesh);

	//SkeltalMeshComponent��RootComponent��Attach
	SkeletalMesh->SetupAttachment(RootComponent);
	//ArrowComponent�̍쐬
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));

	//ArrowComponent�̈ʒu��ݒ�
    ArrowComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	//ArrowComponent��SkeltalMeshComponent��Attach
    ArrowComponent->SetupAttachment(SkeletalMesh);
	//blackboard�Ƀv���C���[��target�Ƃ��ēo�^
	auto player = GetBlackboardComponent();
	if(player)
	{
		player->SetValueAsObject(TEXT("target"),UGameplayStatics::GetPlayerPawn(this,0));
	}

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

