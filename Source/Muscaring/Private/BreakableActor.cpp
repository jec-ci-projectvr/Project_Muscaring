// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	this->GeometryCollectionComponent->SetNotifyBreaks(true);
	this->GeometryCollectionComponent->SetCanEverAffectNavigation(false);
	this->GeometryCollectionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	destroyCount = 2.0f;
}

void ABreakableActor::BeginPlay()
{
	isBreaked = false;
	auto g = this->GeometryCollectionComponent;
	g->OnChaosBreakEvent.AddDynamic(this, &ABreakableActor::OnBreak);

	world = GEngine->GameViewport->GetWorld();

	auto gameInst = world->GetGameInstance();
	auto subSystem = gameInst->GetSubsystem<UBreakableActorManagerSubSystem>();
	subSystem->AddBreakableActor(this);

	Super::BeginPlay();
}

void ABreakableActor::OnBreak(const FChaosBreakEvent& breakEvent)
{
	world->GetTimerManager().SetTimer(timerHandle, this, &ABreakableActor::DestroyActor, destroyCount, false, destroyCount);
	isBreaked = true;
}

bool ABreakableActor::IsResumeTrigger_Implementation()
{
	return isBreaked;
}

void ABreakableActor::DestroyActor()
{
	this->Destroy();
}