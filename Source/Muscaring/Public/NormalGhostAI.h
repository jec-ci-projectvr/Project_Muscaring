#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "NormalGhost.h"
#include "InterfaceGhostState.h"
#include "NormalGhostAI.generated.h"
UCLASS()
class MUSCARING_API ANormalGhostAI : public AAIController, public IInterfaceGhostState
{
	GENERATED_BODY()
public:
	void SetGhostState_Implementation(GhostState state) override;
	void SetMostNearRestArea_Implementation(ARestArea* restArea) override;
	void SetHitInfo_Implementation(bool hit) override;
	ANormalGhostAI(const class FObjectInitializer& ObjectInitializer);
	//blackboardのキーを設定する
	void SetPlayerKey(APawn* InPawn);
	UFUNCTION()
	ANormalGhostAI* GetPlayerKey() const;
	//behaviorTreeComponentのポインタ
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;
	//blackboardComponentのポインタ
	TObjectPtr<UBlackboardComponent> BlackboardComp;

	//ターゲットのキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKey;
	//自身のキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
        FName SelfActorKey;
	//最も近い休憩所を保持するキー
UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName RestAreaKey;
    //オバケの状態のキー
	UPROPERTY(EditDefaultsOnly, Category = "AI")
        FName GhostStateKey;
	//playerと接触した情報のキー
UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName HitKey;
private:
	//AIのpawnを保持
	virtual void OnPossess(APawn* InPawn) override;

	//AIのpawnを解除
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
	//behaviorTreeのポインタ変数
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<UBehaviorTree> BehaviorTree;
	//Ghostのポインタ変数
    UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<ANormalGhost> Ghost;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorTreeComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
