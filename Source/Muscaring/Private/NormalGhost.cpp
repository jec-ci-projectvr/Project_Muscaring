// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhost.h"
#include "PerCeption/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Muscaring/Muscaring.h"
#include "Muscaring/Public/NormalGhostAI.h"
// Sets default values
ANormalGhost::ANormalGhost()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	//����
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//����̋���
	PawnSensingComp->SightRadius = 2000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ANormalGhost::OnSeePlayer);
}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANormalGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalGhost::OnSeePlayer(APawn* Pawn)
{
	ANormalGhostAI* AIController = Cast<ANormalGhostAI>(GetController());
	//�v���C���[
	APawn* Player = Pawn;
	if (AIController && Player)
	{
		//�v���C���[����ݒ�
		AIController->SetPlayerKey(Player);
	}
	//����ɓ�������See�ƕ\��
	UKismetSystemLibrary::PrintString(this, TEXT("See"));
}

