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
	//���E�͈̔͂�ݒ肷��
public:
	UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn);

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
	UFUNCTION()
	void SettingMostNearRestArea();
	//state��setter
	UFUNCTION()
		void SetState(const GhostState state);
    //state��getter
	UFUNCTION()
		GhostState GetState()const;
//restArea��getter
	UFUNCTION()
	ARestArea* GetRestArea() const;
	//restArea��setter
	UFUNCTION()
		void SetRestArea(ARestArea* restArea);
	//target�Ƃ̍ŒZ������getter
	UFUNCTION()
		float GetMinimumDist() const;
	//target�Ƃ̍ŒZ������setter
	UFUNCTION()
		void SetMinimumDist(const float dist);
	//target��getter
	UFUNCTION()
		APawn* GetPlayer() const;
	//target��setter
	UFUNCTION()
		void SetPlayer(APawn* player);
	//NormalGhostAI��getter
	UFUNCTION()
		AGhostAI* GetGhostAI() const;
	//NormalGhostAI��setter
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
		TObjectPtr<ARestArea> restArea_;//restArea�̃|�C���^

	//target�Ƃ̍ŒZ����
	UPROPERTY(EditAnyWhere)
		float minimumDist_;

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
};
