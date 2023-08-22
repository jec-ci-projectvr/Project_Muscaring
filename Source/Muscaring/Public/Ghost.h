// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "Enum_GhostState.h"
#include "PlayerActionEvent.h"
#include "DestroyedRestArea.h"
#include "BeginMoveToPlayer.h"
#include "Ghost.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API AGhost : public ANPC,public IDestroyedRestArea,public IBeginMoveToPlayer
{
	GENERATED_BODY()
public:
	AGhost();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//
	void DestroyedRestArea_Implementation() override;

    void BeginMoveToPlayer_Implementation() override;
public:
	UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
		virtual void ListenSnapFingers();
	UFUNCTION()
		virtual void ListenFakeOut();
UFUNCTION()
    virtual void StepOnRestArea();
	//scarePoint�ɉ�����state��ύX����
	
		virtual void ChangeState();
	
		virtual void ChangeMoveSpeed();
	UFUNCTION()
		void SetDefaultMoveSpeed(const float speed);
	//escapeMoveSpeed��getter
	UFUNCTION()
		float GetDefaultMoveSpeed() const;
	//escapeMoveSpeed��setter
	UFUNCTION()
		void SetEscapeMoveSpeed(const float speed);
	//escapeMoveSpeed��getter
	UFUNCTION()
		float GetEscapeMoveSpeed() const;

	//scarePoint��getter
	UFUNCTION()
		uint32 GetScarePoint() const;
	//scarePoint��setter
	UFUNCTION()
		void SetScarePoint(const uint32 scarePoint);
//�ł��߂�restArea��ݒ肷��
	UFUNCTION()
	void SettingMostNearRestArea();
	//��Ԗڂɋ߂�restArea��ݒ肷��
	//state��setter
	UFUNCTION()
		void SetState(const GhostState state);
    //state��getter
	UFUNCTION()
		GhostState GetState()const;
//restArea��getter
	UFUNCTION()
	ARestArea* GetMostNearRestArea() const;
	//restArea��setter
	UFUNCTION()
		void SetMostNearRestArea(ARestArea* restArea);
//secondNearRestArea��getter
    UFUNCTION()
        ARestArea* GetSecondNearRestArea() const;
//secondNearRestArea��setter
    UFUNCTION()
		void SetSecondNearRestArea(ARestArea* restArea);
	//target��getter
	UFUNCTION()
		APawn* GetPlayer() const;
	//target��setter
	UFUNCTION()
		void SetPlayer(APawn* player);
	//GhostAI��getter
	UFUNCTION()
		AGhostAI* GetGhostAI() const;
	//GhostAI��setter
	UFUNCTION()
		void SetGhostAI(AGhostAI* ghostAI);
	//��x�̂ݎ��E�ɓ��������ǂ�����getter
	UFUNCTION()
		bool GetOnSeeOnce() const;
	//��x�̂ݎ��E�ɓ��������ǂ�����setter
	UFUNCTION()
		void SetOnSeeOnce(const bool onSeeOnce);

private:
	UPROPERTY(EditAnyWhere)
		uint32 scarePoint_;

	UPROPERTY(EditAnyWhere)
		GhostState state_;

	UPROPERTY()
		TObjectPtr<ARestArea> mostNearRestArea_;//restArea�̃|�C���^

	UPROPERTY()
		TObjectPtr<ARestArea> secondNearRestArea_;//��Ԗڂɋ߂�restArea�̃|�C���^


	//pawn�̃|�C���^
	TObjectPtr<APawn> player_;

	//NormalGhostAI�̃|�C���^
	TObjectPtr<class AGhostAI> ghostAI_;


	//��x�̂ݎ��E�ɓ��������ǂ���
	UPROPERTY()
		bool onSeeOnce_;

	UPROPERTY(EditAnyWhere)
		float defaultMoveSpeed_;

	UPROPERTY(EditAnyWhere)
		float escapeMoveSpeed_;

UPROPERTY(EditAnyWhere)
	TObjectPtr<UPlayerActionEvent> PlayerActionEvent;

UPROPERTY()
bool isBeginMoveToPlayer=false;
};
