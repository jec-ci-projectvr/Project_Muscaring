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
	//blackboard�̃L�[��ݒ肷��
	void SetPlayerKey(APawn* InPawn);
	UFUNCTION()
	ANormalGhostAI* GetPlayerKey() const;
	//behaviorTreeComponent�̃|�C���^
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;
	//blackboardComponent�̃|�C���^�ϐ�
	TObjectPtr<UBlackboardComponent> BlackboardComp;

	//�L�[�̖��̂�ێ�����ϐ�
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKey;
private:
	//AI��pawn��ێ�
	virtual void OnPossess(APawn* InPawn) override;

	//AI��pawn������
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;
	//behaviorTree�̃|�C���^�ϐ�
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<UBehaviorTree> BehaviorTree;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorTreeComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
