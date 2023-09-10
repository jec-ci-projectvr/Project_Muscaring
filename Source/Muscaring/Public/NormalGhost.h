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
	//視界の範囲を設定する
public:
	//scarePointに応じてstateを変更する
	UFUNCTION()
	void ChangeState() override;
	//stateに応じて移動速度を変更する
	UFUNCTION()
	void ChangeMoveSpeed() override;
	//オバケの表情を変更する
	void ChangeExpression() override;
	UFUNCTION()
	void LoadAllExpression() override;
	//指ポキ音が聞こえた時の処理
	void ListenSnapFingers() override;
	//猫だまし音が聞こえた時の処理
	void ListenFakeOut() override;
	//休憩所に乗った時の処理
	void StepOnRestArea() override;
};
