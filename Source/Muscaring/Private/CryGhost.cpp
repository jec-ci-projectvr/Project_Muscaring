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
	SetEscapeMoveSpeed(120.f);
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
	IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
}
void ACryGhost::ChangeMoveSpeed()
{
	switch (GetState())
	{
	case GhostState::Approach:
		GetCharacterMovement()->MaxWalkSpeed = GetDefaultMoveSpeed();
		break;
	case GhostState::Scare:
		GetCharacterMovement()->MaxWalkSpeed = GetDefaultMoveSpeed() * 0.6f;
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
void ACryGhost::ListenSnapFingers()
{
	if (GetGhostAI()->GetBehaviorTree()->IsValidLowLevel())
	{
		SetScarePoint(GetScarePoint() + 3);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
void ACryGhost::ListenFakeOut()
{
	SetScarePoint(GetScarePoint() + 10);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
	ChangeState();
	ChangeMoveSpeed();
}
