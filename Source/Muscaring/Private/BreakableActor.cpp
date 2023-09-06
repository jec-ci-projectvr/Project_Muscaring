// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	this->GeometryCollectionComponent->SetNotifyBreaks(true);
	this->GeometryCollectionComponent->SetCanEverAffectNavigation(false);
	this->GeometryCollectionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	this->GeometryCollectionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	this->GeometryCollectionComponent->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Ignore);

	destroyCount = 2.0f;
}

void ABreakableActor::BeginPlay()
{
	isBreaked = false;
	auto g = this->GeometryCollectionComponent;
	g->OnChaosBreakEvent.AddDynamic(this, &ABreakableActor::OnBreak);

	world = GEngine->GameViewport->GetWorld();
	auto subSystem = world->GetSubsystem<UBreakableActorManagerSubSystem>();
	subSystem->AddBreakableActor(this);

	Super::BeginPlay();
}

void ABreakableActor::OnBreak(const FChaosBreakEvent& breakEvent)
{
	if(isBreaked) return;
	isBreaked = true;
	world->GetTimerManager().SetTimer(timerHandle, this, &ABreakableActor::DestroyActor, destroyCount, false, destroyCount);
	//printscreen
	UKismetSystemLibrary::PrintString(world, TEXT("Break"));
}

bool ABreakableActor::IsResumeTrigger_Implementation()
{
	return isBreaked;
}

void ABreakableActor::DestroyActor()
{
	this->Destroy();
}