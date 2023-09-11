// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "Enum_GhostState.h"
#include "PlayerActionEvent.h"
#include "DestroyedRestArea.h"
#include "BeginMoveToPlayer.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
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
		virtual void OnBreak(const FChaosBreakEvent& breakEvent);
UFUNCTION()
    virtual void StepOnRestArea();
	//scarePoint�ɉ�����state��ύX����
		virtual void ChangeState();
	//state�ɉ����Ĉړ����x��ύX����
		virtual void ChangeMoveSpeed();
	//�I�o�P�̕\���ύX����
		virtual void ChangeExpression();

	//�I�o�P�̕\����ꊇ�œǂݍ���
		virtual void LoadAllExpression();
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
//�ł��߂�restArea�Ɠ�Ԗڂɋ߂�restArea��ݒ肷��
	UFUNCTION()
	    void SettingNearRestArea();
	//scarePoint����
	UFUNCTION()
		virtual void RecoverScarePoint(const uint32 recoveryAmount);
	//nextMoveSpeed��getter
	UFUNCTION()
		float GetNextMoveSpeed() const;
	//nextMoveSpeed��setter
	UFUNCTION()
		void SetNextMoveSpeed(const float speed);

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
	//materials��getter
	UFUNCTION()
		TArray<UMaterial*> GetMaterials() const;

private:
	UPROPERTY(EditAnyWhere)
		uint32 scarePoint_;

	UPROPERTY(EditAnyWhere)
		uint32 recoverPoint_;
	UPROPERTY()
		float nextMoveSpeed_;

	UPROPERTY(EditAnyWhere)
		GhostState state_;

	UPROPERTY()
		TObjectPtr<ARestArea> mostNearRestArea_;//restArea�̃|�C���^

	UPROPERTY()
		TObjectPtr<ARestArea> secondNearRestArea_;//��Ԗڂɋ߂�restArea�̃|�C���^

	UPROPERTY(EditAnyWhere)
		TObjectPtr<ARestArea> endRestArea_;//�I���_��restArea�̃|�C���^
	//pawn�̃|�C���^
	TObjectPtr<APawn> player_;

	//NormalGhostAI�̃|�C���^
	TObjectPtr<class AGhostAI> ghostAI_;

	//�I�o�P�̕\��̃}�e���A�����i�[����z��
	TArray<TObjectPtr<UMaterial>> materials_;

	//��x�̂ݎ��E�ɓ��������ǂ���
	UPROPERTY()
		bool onSeeOnce_;

	UPROPERTY(EditAnyWhere)
		float defaultMoveSpeed_;

	UPROPERTY(EditAnyWhere)
		float escapeMoveSpeed_;

UPROPERTY()
	TObjectPtr<UPlayerActionEvent> PlayerActionEvent;
UPROPERTY()
    TObjectPtr<UGeometryCollectionComponent> GeometryCollectionComponent;

UPROPERTY()
bool isBeginMoveToPlayer=false;
};
