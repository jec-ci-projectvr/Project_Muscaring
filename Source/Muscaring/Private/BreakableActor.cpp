// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	this->GeometryCollectionComponent->SetNotifyBreaks(true);
	this->GeometryCollectionComponent->SetCanEverAffectNavigation(false);
	this->GeometryCollectionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	this->GeometryCollectionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	this->GeometryCollectionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->GeometryCollectionComponent->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Ignore);
	this->GeometryCollectionComponent->ObjectType = EObjectStateTypeEnum::Chaos_Object_Sleeping;

	destroyCount = 10.0f;
}

void ABreakableActor::BeginPlay()
{
	isBreaked_ = false;
	auto g = this->GeometryCollectionComponent;
	g->OnChaosBreakEvent.AddDynamic(this, &ABreakableActor::OnBreak);

	world_ = GEngine->GameViewport->GetWorld();
	auto subSystem = world_->GetSubsystem<UBreakableActorManagerSubSystem>();
	subSystem->AddBreakableActor(this);

	Super::BeginPlay();
}

void ABreakableActor::OnBreak(const FChaosBreakEvent& breakEvent)
{
	if(isBreaked_) return;
	isBreaked_ = true;
	UGameplayStatics::PlaySoundAtLocation(world_, breakSound, breakEvent.Location);
	//printscreen
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Break"));
	world_->GetTimerManager().SetTimer(timerHandle_, this, &ABreakableActor::DestroyActor, destroyCount, false, destroyCount);
}

bool ABreakableActor::IsResumeTrigger_Implementation()
{
	return isBreaked_;
}

void ABreakableActor::DestroyActor()
{
	this->Destroy();
}