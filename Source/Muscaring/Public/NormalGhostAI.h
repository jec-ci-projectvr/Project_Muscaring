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
	//blackboard�̃L�[��ݒ肷��
	void SetPlayerKey(APawn* InPawn);
	UFUNCTION()
	ANormalGhostAI* GetPlayerKey() const;
	//behaviorTreeComponent�̃|�C���^
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;
	//blackboardComponent�̃|�C���^
	TObjectPtr<UBlackboardComponent> BlackboardComp;

	//�^�[�Q�b�g�̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKey;
	//���g�̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
        FName SelfActorKey;
	//�ł��߂��x�e����ێ�����L�[
UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName RestAreaKey;
    //�I�o�P�̏�Ԃ̃L�[
	UPROPERTY(EditDefaultsOnly, Category = "AI")
        FName GhostStateKey;
	//player�ƐڐG�������̃L�[
UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName HitKey;
private:
	//AI��pawn��ێ�
	virtual void OnPossess(APawn* InPawn) override;

	//AI��pawn������
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
	//behaviorTree�̃|�C���^�ϐ�
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<UBehaviorTree> BehaviorTree;
	//Ghost�̃|�C���^�ϐ�
    UPROPERTY(EditDefaultsOnly, Category = "AI")
		TObjectPtr<ANormalGhost> Ghost;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorTreeComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
