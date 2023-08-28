// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhost.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Muscaring/Public/NormalGhostAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InterfaceGhostState.h"

// Sets default values
ANormalGhost::ANormalGhost()
	:AGhost()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(60.f);
	SetEscapeMoveSpeed(90.f);
}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	//AIコントローラーを設定
	{
		SetGhostAI(Cast<ANormalGhostAI>(GetController()));
	}
	Super::BeginPlay();
	GetMostNearRestArea()->onRestAreaDelegate.AddDynamic(this, &ANormalGhost::StepOnRestArea);
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



//恐怖値に応じて状態を変更する
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
	IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
}
//状態によって移動速度を変化させる
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
