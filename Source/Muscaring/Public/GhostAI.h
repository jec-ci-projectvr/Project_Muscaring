// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RestArea.h"
#include "Enum_GhostState.h"
#include "InterfaceGhostState.h"
#include "Ghost.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GhostAI.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API AGhostAI : public AAIController, public IInterfaceGhostState
{
	GENERATED_BODY()

public:
	AGhostAI(const class FObjectInitializer& ObjectInitializer);
	void SetGhostState_Implementation(GhostState state) override;
	void SetMostNearRestArea_Implementation(ARestArea* restArea) override;
	void SetHitInfo_Implementation(bool hit) override;
	//blackboard�̃L�[��ݒ肷��
	UFUNCTION()
	void SetPlayerKey(APawn* InPawn);
private:
	//behaviorTreeComponent�̃|�C���^
	TObjectPtr<UBehaviorTreeComponent> behaviorTreeComp_;

	//blackboardComponent�̃|�C���^
	TObjectPtr<UBlackboardComponent> blackboardComp_;

	//�^�[�Q�b�g�̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName targetKey_;
	//���g�̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName selfActorKey_;
	//�ł��߂��x�e����ێ�����L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName restAreaKey_;
	//�I�o�P�̏�Ԃ̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName ghostStateKey_;
	//player�ƐڐG�������̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName hitKey_;
protected:
	//AI��pawn��ێ�
	virtual void OnPossess(APawn* InPawn) override;

	//AI��pawn������
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
private:
	//behaviorTree�̃|�C���^�ϐ�
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<UBehaviorTree> behaviorTree_;
	//Ghost�̃|�C���^�ϐ�
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<AGhost> ghost_;
	//behaviorTree��setter
public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetBehaviorTree(UBehaviorTree* behaviorTree);

	//behaviorTree��getter
	 UFUNCTION(BlueprintCallable, Category = "AI")
     UBehaviorTree* GetBehaviorTree() const;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return behaviorTreeComp_; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return blackboardComp_; }
};
