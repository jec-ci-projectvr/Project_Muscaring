// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceGhostState.h"
#include "Enum_GhostState.h"
#include "GameFramework/Character.h"
#include "Ghost.h"
#include "PlayerActionEvent.h"
#include "NormalGhost.generated.h"
UCLASS()
class MUSCARING_API ANormalGhost : public AGhost
{
	GENERATED_BODY()
		
public:
	// Sets default values for this character's properties
	ANormalGhost();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//���E�͈̔͂�ݒ肷��
public:
	//scarePoint�ɉ�����state��ύX����
	UFUNCTION()
	void ChangeState() override;
	//state�ɉ����Ĉړ����x��ύX����
	UFUNCTION()
	void ChangeMoveSpeed() override;
	//�I�o�P�̕\���ύX����
	void ChangeExpression() override;
	UFUNCTION()
	void LoadAllExpression() override;
	//�w�|�L���������������̏���
	void ListenSnapFingers() override;
	//�L���܂����������������̏���
	void ListenFakeOut() override;
	//�x�e���ɏ�������̏���
	void StepOnRestArea() override;
};
