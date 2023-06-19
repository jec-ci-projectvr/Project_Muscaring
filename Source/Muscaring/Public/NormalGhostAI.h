#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "NormalGhost.h"
#include "NormalGhostAI.generated.h"
UCLASS()
class MUSCARING_API ANormalGhostAI : public AAIController
{
	GENERATED_BODY()
public:
	ANormalGhostAI(const class FObjectInitializer& ObjectInitializer);
	//blackboardのキーを設定する
	void SetPlayerKey(APawn* InPawn);
	UFUNCTION()
	ANormalGhostAI* GetPlayerKey() const;
	//behaviorTreeComponentのポインタ
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;
	//blackboardComponentのポインタ変数
	TObjectPtr<UBlackboardComponent> BlackboardComp;

	//キーの名称を保持する変数
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKey;
private:
	//AIのpawnを保持
	virtual void OnPossess(APawn* InPawn) override;

	//AIのpawnを解除
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;
	//behaviorTreeのポインタ変数
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<UBehaviorTree> BehaviorTree;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorTreeComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
