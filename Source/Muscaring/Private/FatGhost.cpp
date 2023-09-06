// Fill out your copyright notice in the Description page of Project Settings.


#include "FatGhost.h"
#include "InterfaceGhostState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FatGhostAI.h"

AFatGhost::AFatGhost()
	:AGhost()
{
    PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(40.f);
	SetEscapeMoveSpeed(120.f);
	LoadAllExpression();
}
void AFatGhost::BeginPlay()
{
	//AIコントローラーを設定
	{
		SetGhostAI(Cast<AFatGhostAI>(GetController()));
	}
	Super::BeginPlay();
}
void AFatGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AFatGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}
void AFatGhost::ChangeState()
{
	if (GetScarePoint() < 40)
	{
		SetState(GhostState::Approach);
	}
	else if (GetScarePoint() < 80)
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
	IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
	ChangeExpression();
}
void AFatGhost::ChangeMoveSpeed()
{
	switch (GetState())
	{
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
void AFatGhost::LoadAllExpression()
{
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY1")));
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY2")));
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY3")));
}
void AFatGhost::ChangeExpression()
{
	switch (GetState())
	{
	case GhostState::Idle:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY1")));
		break;
	case GhostState::Approach:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY1")));
		break;
	case GhostState::Scare:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY2")));
		break;
	case GhostState::Escape:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY3")));
		break;
	case GhostState::Swoon:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GY3")));
		break;
	default:
		break;
	}
}
void AFatGhost::ListenSnapFingers()
{
	Super::ListenSnapFingers();
}
void AFatGhost::ListenFakeOut()
{
	Super::ListenFakeOut();
}