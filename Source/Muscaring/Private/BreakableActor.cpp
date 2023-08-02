// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

TArray<ABreakableActor*> ABreakableActor::breakableActors;
TArray<UGeometryCollectionComponent*> ABreakableActor::geometryCollectionComponents;

void ABreakableActor::BeginPlay()
{
	isBreaked = false;
	auto g = this->GetComponentByClass<UGeometryCollectionComponent>();
	g->OnChaosBreakEvent.AddDynamic(this, &ABreakableActor::Break);

	//最初のフレームで自分自身とコンポーネントをスタティック配列に追加する
	breakableActors.Add(this);
	geometryCollectionComponents.Add(g);

	world = GEngine->GameViewport->GetWorld();

	Super::BeginPlay();
}

void ABreakableActor::Break(const FChaosBreakEvent& breakEvent)
{
	world->GetTimerManager().SetTimer(timerHandle, this, &ABreakableActor::DestroyActor, destroyCount, false, destroyCount);
	isBreaked = true;
}

bool ABreakableActor::IsResumeTrigger_Implementation()
{
	return CheckBreaked();
}

void ABreakableActor::DestroyActor()
{
	this->Destroy();
}

bool ABreakableActor::CheckBreaked()
{
	return isBreaked;
}

TArray<ABreakableActor*> ABreakableActor::GetBreakableActors() 
{
	return breakableActors;
}

TArray<UGeometryCollectionComponent*> ABreakableActor::GetGeometryCollectionComponents()
{
	return geometryCollectionComponents;
}
