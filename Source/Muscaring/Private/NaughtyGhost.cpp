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
void ANaughtyGhost::ListenSnapFingers()
{
	if (GetGhostAI()->GetBehaviorTree()->IsValidLowLevel())
	{
		SetScarePoint(GetScarePoint() + 3);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
void ANaughtyGhost::ListenFakeOut()
{
	if (GetGhostAI()->GetBehaviorTree()->IsValidLowLevel())
	{
		SetScarePoint(GetScarePoint() + 10);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
