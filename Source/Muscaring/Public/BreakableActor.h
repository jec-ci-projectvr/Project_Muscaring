// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "BreakableActor.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ABreakableActor : public AGeometryCollectionActor
{
	GENERATED_BODY()

	static TArray<ABreakableActor*> breakableActors; //breakableActors�����ׂē������X�^�e�B�b�N�z��
	static TArray<UGeometryCollectionComponent*> geometryCollectionComponents; //�W�I���g���R���N�V���������ׂē������X�^�e�B�b�N�z��

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
	static TArray<ABreakableActor*> GetBreakableActors(); //���ׂĂ�BreakableActors�̎擾

	UFUNCTION(BlueprintPure)
	static TArray<UGeometryCollectionComponent*> GetGeometryCollectionComponents(); //���ׂẴW�I���g���R���N�V�����̎擾
};
