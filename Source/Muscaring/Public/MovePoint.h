// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MoveResumeTrigger.h"
#include "MovePoint.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointArrival, AMovePoint*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointDeparture, AMovePoint*, AMovePoint*);

UCLASS()
class MUSCARING_API AMovePoint : public AActor
{
	GENERATED_BODY()

	// Scene Component
	TObjectPtr<USceneComponent> defaultSceneRoot_;

	// StaticMesh Component
	TObjectPtr<UStaticMeshComponent> staticMesh_;

	//�ŏ��ɓ��B����ׂ��|�C���g��
	UPROPERTY(EditAnywhere, Category = "Entry")
	bool entryPoint_;

	//���̒n�_�ɓ��B����ƈꎞ��~�����邩
	UPROPERTY(EditAnywhere, Category = "Event")
	bool waitPoint_;

	//�ꎞ��~����������g���K�[�ƂȂ�A�N�^�[(IMoveResumeTrigger���������ꂽ�I�u�W�F�N�g�ł���K�v������)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "waitPoint"), Category = "Event")
	TObjectPtr<AActor> resumeTriggerObject_;

	//���̒n�_�ŉ�]�����邩
	UPROPERTY(EditAnywhere, Category = "Event")
	bool rotate_;

	//���B�����Ɣ��肷�鋗��
	UPROPERTY(EditAnywhere, Category = "General")
	float arrivalDistance_;

	//���̃|�C���g�̎��ɓ��B����|�C���g
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AMovePoint> nextPoint_;

	//���̃|�C���g��Ǐ]����A�N�^�[("�Ȃ�"���ƃv���C���[�ɂȂ�܂�)
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AActor> targetActor_;

	//���B�ς݂��ǂ���
	bool isArrived_;

	//MovePoint���L�����ǂ���
	bool isActive_;

	//���B�����Ƃ��̏���
	void Arrival();

	//�o�������Ƃ��̏���
	void Departure();
	
	//�^�[�Q�b�g�Ƃ̋������`�F�b�N
	bool CheckDistance();

	//�ꎞ��~����������g���K�[���L�����ǂ����`�F�b�N
	bool CheckResumeTrigger();

public:	
	// Sets default values for this actor's properties
	AMovePoint();

	TObjectPtr<AActor> GetTargetActor() { return targetActor_; }

	bool IsEntryPoint() { return entryPoint_; }

	bool IsWaitPoint() { return waitPoint_; }

	bool IsRotate() { return rotate_; }

	void SetActive(bool active) { isActive_ = active; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPointArrival OnPointArrival;

	FOnPointDeparture OnPointDeparture;

};
