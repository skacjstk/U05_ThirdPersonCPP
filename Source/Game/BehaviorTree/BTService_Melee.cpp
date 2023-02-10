#include "BTService_Melee.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Characters/CEnemy_AI.h"
#include "CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

UBTService_Melee::UBTService_Melee()
{
	NodeName = "Melee";
}

void UBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Null 체크 해야함
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	
	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();	// StateComponent랑 비슷함 
		return;
	}
	ACPlayer* target = behavior->GetTargetPlayer();
	if (target == nullptr)
	{
		behavior->SetWaitMode();
		return;
		// 아직 순찰경로가 없음 
	}

	float distance = aiPawn->GetDistanceTo(target);

	// 공격범위보다 가까우면
	if (distance < controller->GetBehaviorRange())
	{
		behavior->SetActionMode();
		return;

		// 돌격거리보다 가까우면
		if (distance < controller->GetSightRadius())
		{
			behavior->SetApproachMode();
			return;
		}
	}
}

