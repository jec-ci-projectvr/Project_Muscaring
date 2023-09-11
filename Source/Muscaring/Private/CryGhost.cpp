// Fill out your copyright notice in the Description page of Project Settings.


#include "CryGhost.h"
#include "Kismet/GameplayStatics.h"
#include "InterfaceGhostState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CryGhostAI.h"

ACryGhost::ACryGhost() 
	:AGhost()
{
	PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(60.f);
	SetEscapeMoveSpeed(150.f);
	LoadAllExpression();
}
void ACryGhost::BeginPlay()
{
	//AIコントローラーを設定
	{
		SetGhostAI(Cast<ACryGhostAI>(GetController()));
	}
	Super::BeginPlay();
}
void ACryGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ACryGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}
void ACryGhost::ChangeState()
{
	if (GetScarePoint() < 20)
	{
		SetState(GhostState::Approach);
	}
	else if (GetScarePoint() < 50)
	{
		SetState(GhostState::Scare);
	}
	else if (GetScarePoint() < 100)
	{
		SetState(GhostState::Escape);
	}
	else if (GetScarePoint() >= 100)
	{
		SetState(GhostState::Swoon);
	}
	ChangeExpression();
}
void ACryGhost::ChangeMoveSpeed()
{
	switch (GetState())
	{
	case GhostState::Idle:
		SetNextMoveSpeed(0.f);
		break;
	case GhostState::Approach:
		SetNextMoveSpeed(GetDefaultMoveSpeed());
		break;
	case GhostState::Scare:
		SetNextMoveSpeed(GetDefaultMoveSpeed() * 0.6f);
		break;
	case GhostState::Escape:
		SetNextMoveSpeed(GetEscapeMoveSpeed());
		break;
	case GhostState::Swoon:
		SetNextMoveSpeed(0.f);
		break;
	default:
		break;
	}
}
void ACryGhost::LoadAllExpression()
{
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB1")));
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB2")));
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB3")));
}
void ACryGhost::ChangeExpression()
{
	/*switch (GetState())
	{
	case GhostState::Idle:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB1")));
		break;
	case GhostState::Approach:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB1")));
		break;
	case GhostState::Scare:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB2")));
		break;
	case GhostState::Escape:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB3")));
		break;
	case GhostState::Swoon:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GB3")));
		break;
	default:
		break;
	}*/
	/*switch (GetState())
	{
	case GhostState::Approach:
		GetMesh()->SetMaterial(0, GetMaterials()[0]);
		break;
	case GhostState::Scare:
		GetMesh()->SetMaterial(0, GetMaterials()[1]);
		break;
	case GhostState::Escape:
		GetMesh()->SetMaterial(0, GetMaterials()[2]);
		break;
	case GhostState::Swoon:
		GetMesh()->SetMaterial(0, GetMaterials()[2]);
		break;
	}*/
}
void ACryGhost::ListenSnapFingers()
{
	Super::ListenSnapFingers();
}
void ACryGhost::ListenFakeOut()
{
	Super::ListenFakeOut();
}
