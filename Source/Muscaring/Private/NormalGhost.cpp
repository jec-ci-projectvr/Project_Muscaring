// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhost.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Muscaring/Public/NormalGhostAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InterfaceGhostState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANormalGhost::ANormalGhost()
	:AGhost()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(60.f);
	SetEscapeMoveSpeed(150.f);
	LoadAllExpression();
}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	ChangeExpression();
	//AI�R���g���[���[��ݒ�
	{
		SetGhostAI(Cast<ANormalGhostAI>(GetController()));
	}
	Super::BeginPlay();
}

// Called every frame
void ANormalGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ANormalGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}



//���|�l�ɉ����ď�Ԃ�ύX����
void ANormalGhost::ChangeState()
{
	if(GetScarePoint()<30)
	{
		SetState(GhostState::Approach);
	}
	else if(GetScarePoint()<60)
	{
		SetState(GhostState::Scare);
	}
	else if (GetScarePoint()<100)
	{
		SetState(GhostState::Escape);
	}
	else if (GetScarePoint() >= 100)
	{
		SetState(GhostState::Swoon);
	}
	ChangeExpression();
}
//��Ԃɂ���Ĉړ����x��ω�������
void ANormalGhost::ChangeMoveSpeed()
{
	switch (GetState())
	{
	case GhostState::Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	case GhostState::Approach:
		GetCharacterMovement()->MaxWalkSpeed = GetDefaultMoveSpeed();
		break;
	case GhostState::Scare:
		GetCharacterMovement()->MaxWalkSpeed = GetDefaultMoveSpeed() * 0.8f;
		break;
	case GhostState::Escape:
		GetCharacterMovement()->MaxWalkSpeed = GetEscapeMoveSpeed();
		break;
	case GhostState::Swoon:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	default:
		break;
	}
}
void ANormalGhost::ChangeExpression()
{
	switch (GetState())
	{
	case GhostState::Approach:
		//GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN1")));
		GetMesh()->SetMaterial(0, GetMaterials()[0]);
		break;
	case GhostState::Scare:
		//GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN2")));
		GetMesh()->SetMaterial(0, GetMaterials()[1]);
		break;
	case GhostState::Escape:
		//GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN3")));
		GetMesh()->SetMaterial(0, GetMaterials()[1]);
		break;
	case GhostState::Swoon:
		//GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN3")));
		GetMesh()->SetMaterial(0, GetMaterials()[2]);
		break;
	default:
		GetMesh()->SetMaterial(0, GetMaterials()[0]);
		break;
	}
}
void ANormalGhost::LoadAllExpression()
{
	GetMaterials().Add(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN1")));
	GetMaterials().Add(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN2")));
	GetMaterials().Add(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN3")));
}
void ANormalGhost::ListenSnapFingers()
{
	Super::ListenSnapFingers();
}
void ANormalGhost::ListenFakeOut()
{
	Super::ListenFakeOut();
}
void ANormalGhost::StepOnRestArea()
{	
}
