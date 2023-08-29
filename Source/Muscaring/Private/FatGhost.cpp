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
void AFatGhost::ListenSnapFingers()
{
	if (GetGhostAI()->GetBehaviorTree()->IsValidLowLevel())
	{
		SetScarePoint(GetScarePoint() + 3);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
void AFatGhost::ListenFakeOut()
{
	if (GetGhostAI()->GetBehaviorTree()->IsValidLowLevel())
	{
		SetScarePoint(GetScarePoint() + 10);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}