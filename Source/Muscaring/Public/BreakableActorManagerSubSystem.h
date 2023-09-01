// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MuscaringWorldSettings.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "BreakableActorManagerSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API UBreakableActorManagerSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	TArray<AActor*> breakableActors; //breakableActorsの配列

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION(BlueprintCallable)
	void AddBreakableActor(AActor* actor) { breakableActors.Add(actor); } //配列にBreakableActorを追加

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetBreakableActors() { return breakableActors; }  //すべてのBreakableActorの取得

	UFUNCTION(BlueprintPure)
	TArray<UGeometryCollectionComponent*> GetGeometryCollectionComponents(); //すべてのジオメトリコレクションの取得
};
