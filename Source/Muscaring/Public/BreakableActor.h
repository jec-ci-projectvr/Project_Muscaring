// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MoveResumeTrigger.h"
#include "BreakableActor.generated.h"

UCLASS()
class MUSCARING_API ABreakableActor : public AGeometryCollectionActor, public IMoveResumeTrigger
{
	GENERATED_BODY()

	bool isBreaked; //破壊された後か 
	static TArray<ABreakableActor*> breakableActors; //breakableActorsがすべて入ったスタティック配列
	static TArray<UGeometryCollectionComponent*> geometryCollectionComponents; //ジオメトリコレクションがすべて入ったスタティック配列

	UWorld* world;
	FTimerHandle timerHandle;

	UFUNCTION()
	void Break(const FChaosBreakEvent& breakEvent); //破壊された時に呼ばれる関数

	UFUNCTION()
	void DestroyActor();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float destroyCount; //破壊されてから消えるまでのカウント

public:

	UFUNCTION(BlueprintPure)
	bool CheckBreaked();

	UFUNCTION(BlueprintPure)
	static TArray<ABreakableActor*> GetBreakableActors(); //すべてのBreakableActorsの取得

	UFUNCTION(BlueprintPure)
	static TArray<UGeometryCollectionComponent*> GetGeometryCollectionComponents(); //すべてのジオメトリコレクションの取得

	virtual bool IsResumeTrigger_Implementation() override;

};
