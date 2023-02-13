#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Action.generated.h"

UCLASS()
class GAME_API UBTTaskNode_Action : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Action();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere)
		float Delay = 2.0f;
	float TotalTime;
};