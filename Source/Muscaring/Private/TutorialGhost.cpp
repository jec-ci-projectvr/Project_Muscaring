// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGhost.h"
#include "InterfaceGhostState.h"
#include "NormalGhostAI.h"
#include "GameFramework/CharacterMovementComponent.h"

ATutorialGhost::ATutorialGhost()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ATutorialGhost::BeginPlay()
{
	//AIコントローラーを設定
	{
		SetGhostAI(Cast<ANormalGhostAI>(GetController()));
	}
	Super::BeginPlay();
}
void ATutorialGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ATutorialGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}
void ATutorialGhost::ChangeState()
{
	if (GetScarePoint() < 50)
	{
		SetState(GhostState::Approach);
	}
	else if (GetScarePoint() >= 50)
	{
		SetState(GhostState::Swoon);
	}
	IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
}
void ATutorialGhost::ChangeMoveSpeed()
{
	if (GetState() == GhostState::Approach)
		GetCharacterMovement()->MaxWalkSpeed = GetDefaultMoveSpeed();
    else if (GetState() == GhostState::Swoon)
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
}
void ATutorialGhost::ListenSnapFingers()
{
	SetScarePoint(GetScarePoint() + 10);
	ChangeState();
	ChangeMoveSpeed();
}
void ATutorialGhost::ListenFakeOut()
{
	SetScarePoint(GetScarePoint() + 50);
	ChangeState();
	ChangeMoveSpeed();
}
