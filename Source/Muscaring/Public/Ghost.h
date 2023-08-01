// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "RestArea.h"
#include "Enum_GhostState.h"
#include "Ghost.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API AGhost : public ANPC
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
	//視界の範囲を設定する
public:
	UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn);

	//scarePointに応じてstateを変更する
	
		virtual void ChangeState();
	
		virtual void ChangeMoveSpeed();
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
	UFUNCTION()
	void SettingMostNearRestArea();
	//stateのsetter
	UFUNCTION()
		void SetState(const GhostState state);
    //stateのgetter
	UFUNCTION()
		GhostState GetState()const;
//restAreaのgetter
	UFUNCTION()
	ARestArea* GetRestArea() const;
	//restAreaのsetter
	UFUNCTION()
		void SetRestArea(ARestArea* restArea);
	//targetとの最短距離のgetter
	UFUNCTION()
		float GetMinimumDist() const;
	//targetとの最短距離のsetter
	UFUNCTION()
		void SetMinimumDist(const float dist);
	//targetのgetter
	UFUNCTION()
		APawn* GetPlayer() const;
	//targetのsetter
	UFUNCTION()
		void SetPlayer(APawn* player);
	//NormalGhostAIのgetter
	UFUNCTION()
		AGhostAI* GetGhostAI() const;
	//NormalGhostAIのsetter
	UFUNCTION()
		void SetGhostAI(AGhostAI* ghostAI);
	//一度のみ視界に入ったかどうかのgetter
	UFUNCTION()
		bool GetOnSeeOnce() const;
	//一度のみ視界に入ったかどうかのsetter
	UFUNCTION()
		void SetOnSeeOnce(const bool onSeeOnce);

private:
	UPROPERTY(EditAnyWhere)
		uint32 scarePoint_;

	UPROPERTY(EditAnyWhere)
		GhostState state_;

	UPROPERTY()
		TObjectPtr<ARestArea> restArea_;//restAreaのポインタ

	//targetとの最短距離
	UPROPERTY(EditAnyWhere)
		float minimumDist_;

	//pawnのポインタ
	TObjectPtr<APawn> player_;

	//NormalGhostAIのポインタ
	TObjectPtr<class AGhostAI> ghostAI_;


	//一度のみ視界に入ったかどうか
	UPROPERTY()
		bool onSeeOnce_;

	UPROPERTY(EditAnyWhere)
		float defaultMoveSpeed_;

	UPROPERTY(EditAnyWhere)
		float escapeMoveSpeed_;
};
