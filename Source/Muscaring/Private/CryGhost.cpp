// Fill out your copyright notice in the Description page of Project Settings.


#include "CryGhost.h"
#include "NormalGhost.h"
#include "InterfaceGhostState.h"
#include "Enum_GhostState.h"
#include "GameFramework/Character.h"
#include "CryGhost.generated.h"

ACryGhost::ACryGhost()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(40.f);
	SetEscapeMoveSpeed(80.f);
}
void ACryGhost::ChangeState()
{
	if (GetScarePoint() < 30)
	{
		state_ = GhostState::Approach;
	}
	else if (scarePoint_ < 60)
	{
		state_ = GhostState::Scare;
	}
	else if (scarePoint_ < 100)
	{
		state_ = GhostState::Escape;
	}
	else if (scarePoint_ >= 100)
	{
		state_ = GhostState::Swoon;
	}
}
//ó‘Ô‚É‚æ‚Á‚ÄˆÚ“®‘¬“x‚ð•Ï‰»‚³‚¹‚é
void ACryGhost::ChangeMoveSpeed()
{
	switch (state_)
	{
	case GhostState::Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	case GhostState::Approach:
		GetCharacterMovement()->MaxWalkSpeed = defaultMoveSpeed;
		break;
	case GhostState::Scare:
		GetCharacterMovement()->MaxWalkSpeed = defaultMoveSpeed / 2;
		break;
	case GhostState::Escape:
		GetCharacterMovement()->MaxWalkSpeed = escapeMoveSpeed;
		break;
	case GhostState::Swoon:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	default:
		break;
	}
}
