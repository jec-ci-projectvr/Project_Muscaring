// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MoveResumeTrigger.h"
#include "MovePoint.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointArrival, AMovePoint*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointDeparture, AMovePoint*, AMovePoint*);

UCLASS()
class MUSCARING_API AMovePoint : public AActor
{
	GENERATED_BODY()

	// Scene Component
	TObjectPtr<USceneComponent> defaultSceneRoot;

	// StaticMesh Component
	TObjectPtr<UStaticMeshComponent> staticMesh;

public:	
	// Sets default values for this actor's properties
	AMovePoint();

	TObjectPtr<AMovePoint> targetDistination;

	//�ŏ��ɓ��B����ׂ��|�C���g��
	UPROPERTY(EditAnywhere, Category = "Entry")
	bool entryPoint;

	//���̒n�_�ɓ��B����ƈꎞ��~�����邩
	UPROPERTY(EditAnywhere, Category = "Wait")
	bool waitPoint;

	//�ꎞ��~����������g���K�[�ƂȂ�A�N�^�[(IMoveResumeTrigger���������ꂽ�I�u�W�F�N�g�ł���K�v������)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "waitPoint"), Category = "Wait")
	TObjectPtr<AActor> resumeTriggerObject;

	//���B�����Ɣ��肷�鋗��
	UPROPERTY(EditAnywhere, Category = "General")
	float arrivalDistance;

	//���̃|�C���g�̎��ɓ��B����|�C���g
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AMovePoint> nextPoint;

	//���̃|�C���g��Ǐ]����A�N�^�[("�Ȃ�"���ƃv���C���[�ɂȂ�܂�)
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AActor> targetActor;

	//�Q�[�����Ƀ|�C���g�̃��b�V����\�������邩
	UPROPERTY(EditAnywhere, Category = "Visible")
	bool displayMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	IMoveResumeTrigger* resumeTrigger;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPointArrival OnPointArrival;

	FOnPointDeparture OnPointDeparture;

};
