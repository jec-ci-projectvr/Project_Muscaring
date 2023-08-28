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
	virtual void ChangeState() override;
	//state�ɉ����Ĉړ����x��ύX����
	UFUNCTION()
	void ChangeMoveSpeed() override;
	//�w�|�L���������������̏���
	virtual void ListenSnapFingers() override;
	//�L���܂����������������̏���
	virtual void ListenFakeOut() override;
	//�x�e���ɏ�������̏���
	virtual void StepOnRestArea() override;
};
