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
	AGhostAI();
	void SetGhostState_Implementation(GhostState state) override;
	void SetMostNearRestArea_Implementation(ARestArea* restArea) override;
	void SetHitInfo_Implementation(bool hit) override;
    void SetSecondNearRestArea_Implementation(ARestArea* restArea) override;
	//blackboardのキーを設定する
	UFUNCTION()
	void SetPlayerKey(APawn* InPawn);
private:
	//behaviorTreeComponentのポインタ
	TObjectPtr<UBehaviorTreeComponent> behaviorTreeComp_;

	//blackboardComponentのポインタ
	TObjectPtr<UBlackboardComponent> blackboardComp_;
	//PlayerActionEventのポインタ
	TObjectPtr<UPlayerActionEvent> PlayerActionEvent;

	//ターゲットのキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName targetKey_;
	//自身のキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName selfActorKey_;
	//最も近い休憩所を保持するキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName mostNearRestAreaKey_;
	//二番目に近い休憩所を保持するキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName secondNearRestAreaKey_;
	//オバケの状態のキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName ghostStateKey_;
	//playerと接触した情報のキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName hitKey_;
protected:
	//AIのpawnを保持
	virtual void OnPossess(APawn* InPawn) override;

	//AIのpawnを解除
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
private:
	//behaviorTreeのポインタ変数
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<UBehaviorTree> behaviorTree_;
	//Ghostのポインタ変数
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<AGhost> ghost_;
	//behaviorTreeのsetter
public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetBehaviorTree(UBehaviorTree* behaviorTree);

	//behaviorTreeのgetter
	 UFUNCTION(BlueprintCallable, Category = "AI")
     UBehaviorTree* GetBehaviorTree() const;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return behaviorTreeComp_; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return blackboardComp_; }
};
