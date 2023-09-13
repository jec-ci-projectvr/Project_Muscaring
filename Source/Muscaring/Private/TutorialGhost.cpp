// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGhost.h"
#include "InterfaceGhostState.h"
#include "NormalGhostAI.h"
#include "GameFramework/CharacterMovementComponent.h"

ATutorialGhost::ATutorialGhost()
	:AGhost()
{
	PrimaryActorTick.bCanEverTick = true;
	SetDefaultMoveSpeed(150.f);
	SetEscapeMoveSpeed(210.f);
}
void ATutorialGhost::BeginPlay()
{
	//AI�R���g���[���[��ݒ�
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
	if (GetScarePoint() >= 1)
		SetState(GhostState::Approach);
	if (snapFingersFlag && fakeOutFlag)
	{
		SetState(GhostState::Swoon);
		IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
		ChangeExpression();
	}
}
void ATutorialGhost::ChangeMoveSpeed()
{
	if (GetState() == GhostState::Approach)
		GetCharacterMovement()->MaxWalkSpeed = GetDefaultMoveSpeed();
    else if (GetState() == GhostState::Swoon)
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
}
void ATutorialGhost::ChangeExpression()
{
	switch (GetState())
	{
	case GhostState::Approach:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN1")));
		//GetMesh()->SetMaterial(0, GetMaterials()[0]);
		break;
	case GhostState::Scare:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN2")));
		//GetMesh()->SetMaterial(0, GetMaterials()[1]);
		break;
	case GhostState::Escape:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN3")));
		//GetMesh()->SetMaterial(0, GetMaterials()[1]);
		break;
	case GhostState::Swoon:
		GetMesh()->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN3")));
		//GetMesh()->SetMaterial(0, GetMaterials()[2]);
		break;
	default:
		//GetMesh()->SetMaterial(0, GetMaterials()[0]);
		break;
	}
}
void ATutorialGhost::LoadAllExpression()
{
	GetMaterials().Add(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN1")));
	GetMaterials().Add(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN2")));
	GetMaterials().Add(LoadObject<UMaterial>(nullptr, TEXT("/Game/Characters/Ghosts/M_GN3")));
}
void ATutorialGhost::ListenSnapFingers()
{
	//�v���C���[�Ƃ̋������v��(�������܂܂Ȃ�)
	const float distance = FVector::Dist2D(GetPlayer()->GetActorLocation(), GetActorLocation());
	//��������͈͓��ł���Ύ��s
	if (GetState() != GhostState::Idle)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetFakeOut(GetGhostAI(), true);
		IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
		snapFingersFlag = true;
	}
}
void ATutorialGhost::ListenFakeOut()
{
	//�v���C���[�Ƃ̋������v��(�������܂܂Ȃ�)
	const float distance = FVector::Dist2D(GetPlayer()->GetActorLocation(), GetActorLocation());
	//��������͈͓��ł���Ύ��s
	if (GetState() != GhostState::Idle)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetFakeOut(GetGhostAI(), true);
		IInterfaceGhostState::Execute_SetGhostState(GetGhostAI(), GetState());
		fakeOutFlag = true;
	}
}
