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

	bool isBreaked; //�j�󂳂ꂽ�ォ 
	static TArray<ABreakableActor*> breakableActors; //breakableActors�����ׂē������X�^�e�B�b�N�z��
	static TArray<UGeometryCollectionComponent*> geometryCollectionComponents; //�W�I���g���R���N�V���������ׂē������X�^�e�B�b�N�z��

	UWorld* world;
	FTimerHandle timerHandle;

	UFUNCTION()
	void Break(const FChaosBreakEvent& breakEvent); //�j�󂳂ꂽ���ɌĂ΂��֐�

	UFUNCTION()
	void DestroyActor();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float destroyCount; //�j�󂳂�Ă��������܂ł̃J�E���g

public:

	UFUNCTION(BlueprintPure)
	bool CheckBreaked();

	UFUNCTION(BlueprintPure)
	static TArray<ABreakableActor*> GetBreakableActors(); //���ׂĂ�BreakableActors�̎擾

	UFUNCTION(BlueprintPure)
	static TArray<UGeometryCollectionComponent*> GetGeometryCollectionComponents(); //���ׂẴW�I���g���R���N�V�����̎擾

	virtual bool IsResumeTrigger_Implementation() override;

};
