// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "BreakableActorManagerSubSystem.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MoveResumeTrigger.h"
#include "BreakableActor.generated.h"

UCLASS()
class MUSCARING_API ABreakableActor : public AGeometryCollectionActor, public IMoveResumeTrigger
{
	GENERATED_BODY()

	bool isBreaked_; //破壊された後か 

	UWorld* world_;
	FTimerHandle timerHandle_;

	UFUNCTION()
	void OnBreak(const FChaosBreakEvent& breakEvent); //破壊された時に呼ばれる関数

	UFUNCTION()
	void DestroyActor(); //アクターの削除
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float destroyCount; //破壊されてから消えるまでのカウント

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* breakSound; //破壊された時に鳴らす音


public:
	ABreakableActor();

	UFUNCTION(BlueprintCallable)
	void SetBreaked(bool breaked) { isBreaked_ = breaked; }

	UFUNCTION(BlueprintPure)
	bool IsBreaked() { return isBreaked_; }

	bool IsResumeTrigger_Implementation() override;

};
