// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhost.h"
#include "PerCeption/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Muscaring/Muscaring.h"
#include "Muscaring/Public/NormalGhostAI.h"
#include "Muscaring/Public/NormalGhost.h"
#include <Kismet/GameplayStatics.h>
#include "RestArea.h"
#include "Enum_GhostState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerActionEvent.h"
#include "InterfaceGhostState.h"

// Sets default values
ANormalGhost::ANormalGhost()
	:AGhost()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	//AI�R���g���[���[��ݒ�
	{
		SetGhostAI(Cast<ANormalGhostAI>(GetController()));
	}
	Super::BeginPlay();
	PlayerActionEvent = Cast<UPlayerActionEvent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UPlayerActionEvent::StaticClass()));

	if (PlayerActionEvent == nullptr) 
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "not found event");
	}
	PlayerActionEvent->OnSnapFingers.AddDynamic(this, &ANormalGhost::ListenSnapFingers);
	PlayerActionEvent->OnFakeOut.AddDynamic(this, &ANormalGhost::ListenFakeOut);
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
	IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
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
void ANormalGhost::ListenSnapFingers()
{
	SetScarePoint(GetScarePoint() + 3);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
	ChangeState();
	ChangeMoveSpeed();
}
void ANormalGhost::ListenFakeOut()
{
	SetScarePoint(GetScarePoint() + 10);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
	ChangeState();
	ChangeMoveSpeed();
}
void ANormalGhost::StepOnRestArea()
{	
	SettingMostNearRestArea();
}
