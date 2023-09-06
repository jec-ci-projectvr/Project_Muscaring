// Fill out your copyright notice in the Description page of Project Settings.


#include "NaughtyGhost.h"
#include "InterfaceGhostState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NaughtyGhostAI.h"

ANaughtyGhost::ANaughtyGhost()
	:AGhost()
{
    PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(90.f);
	SetEscapeMoveSpeed(180.f);
	LoadAllExpression();
}
void ANaughtyGhost::BeginPlay()
{
	//AIコントローラーを設定
	{
		SetGhostAI(Cast<ANaughtyGhostAI>(GetController()));
	}
	Super::BeginPlay();
}
void ANaughtyGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ANaughtyGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}
void ANaughtyGhost::ChangeState()
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
void ANaughtyGhost::ChangeMoveSpeed()
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
void ANaughtyGhost::LoadAllExpression()
{
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR1")));
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR2")));
	GetMaterials().Push(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR3")));
}
void ANaughtyGhost::ChangeExpression()
{
	switch (GetState())
	{
	case GhostState::Idle:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR1")));
		break;
	case GhostState::Approach:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR1")));
		break;
	case GhostState::Scare:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR2")));
		break;
	case GhostState::Escape:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR3")));
		break;
	case GhostState::Swoon:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GR3")));
		break;
	default:
		break;
	}
}
void ANaughtyGhost::ListenSnapFingers()
{
	Super::ListenSnapFingers();
}
void ANaughtyGhost::ListenFakeOut()
{
	Super::ListenFakeOut();
}
