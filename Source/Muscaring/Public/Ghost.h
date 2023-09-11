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
	//scarePointに応じてstateを変更する
		virtual void ChangeState();
	//stateに応じて移動速度を変更する
		virtual void ChangeMoveSpeed();
	//オバケの表情を変更する
		virtual void ChangeExpression();

	//オバケの表情を一括で読み込む
		virtual void LoadAllExpression();
	UFUNCTION()
		void SetDefaultMoveSpeed(const float speed);
	//escapeMoveSpeedのgetter
	UFUNCTION()
		float GetDefaultMoveSpeed() const;
	//escapeMoveSpeedのsetter
	UFUNCTION()
		void SetEscapeMoveSpeed(const float speed);
	//escapeMoveSpeedのgetter
	UFUNCTION()
		float GetEscapeMoveSpeed() const;

	//scarePointのgetter
	UFUNCTION()
		uint32 GetScarePoint() const;
	//scarePointのsetter
	UFUNCTION()
		void SetScarePoint(const uint32 scarePoint);
//最も近いrestAreaと二番目に近いrestAreaを設定する
	UFUNCTION()
	    void SettingNearRestArea();
	//scarePointを回復
	UFUNCTION()
		virtual void RecoverScarePoint(const uint32 recoveryAmount);
	//nextMoveSpeedのgetter
	UFUNCTION()
		float GetNextMoveSpeed() const;
	//nextMoveSpeedのsetter
	UFUNCTION()
		void SetNextMoveSpeed(const float speed);

	//stateのsetter
	UFUNCTION()
		void SetState(const GhostState state);
    //stateのgetter
	UFUNCTION()
		GhostState GetState()const;
//restAreaのgetter
	UFUNCTION()
	ARestArea* GetMostNearRestArea() const;
	//restAreaのsetter
	UFUNCTION()
		void SetMostNearRestArea(ARestArea* restArea);
//secondNearRestAreaのgetter
    UFUNCTION()
        ARestArea* GetSecondNearRestArea() const;
//secondNearRestAreaのsetter
    UFUNCTION()
		void SetSecondNearRestArea(ARestArea* restArea);
	//targetのgetter
	UFUNCTION()
		APawn* GetPlayer() const;
	//targetのsetter
	UFUNCTION()
		void SetPlayer(APawn* player);
	//GhostAIのgetter
	UFUNCTION()
		AGhostAI* GetGhostAI() const;
	//GhostAIのsetter
	UFUNCTION()
		void SetGhostAI(AGhostAI* ghostAI);
	//materialsのgetter
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
		TObjectPtr<ARestArea> mostNearRestArea_;//restAreaのポインタ

	UPROPERTY()
		TObjectPtr<ARestArea> secondNearRestArea_;//二番目に近いrestAreaのポインタ

	UPROPERTY(EditAnyWhere)
		TObjectPtr<ARestArea> endRestArea_;//終着点のrestAreaのポインタ
	//pawnのポインタ
	TObjectPtr<APawn> player_;

	//NormalGhostAIのポインタ
	TObjectPtr<class AGhostAI> ghostAI_;

	//オバケの表情のマテリアルを格納する配列
	TArray<TObjectPtr<UMaterial>> materials_;

	//一度のみ視界に入ったかどうか
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
