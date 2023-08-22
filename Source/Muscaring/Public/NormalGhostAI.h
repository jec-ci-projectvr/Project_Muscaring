#pragma once
#include "CoreMinimal.h"
//#include "AIController.h"
//#include "BehaviorTree/BehaviorTree.h"
//#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "BehaviorTree/BlackboardComponent.h" 
//#include "NormalGhost.h"
#include "GhostAI.h"
#include "NormalGhostAI.generated.h"
UCLASS()
class MUSCARING_API ANormalGhostAI : public AGhostAI
{
	GENERATED_BODY()
public:
	ANormalGhostAI();

private:

	//AIのpawnを保持
	virtual void OnPossess(APawn* InPawn) override;

	//AIのpawnを解除
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
};
