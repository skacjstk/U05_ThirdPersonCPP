#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(character);
	CheckNull(action);
	action->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	//if (character == nullptr) return;
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
//	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());	
	Direction = CalculateDirection(character->GetVelocity(), character->GetActorForwardVector().Rotation());

	UCFootComponent* foot = CHelpers::GetComponent<UCFootComponent>(character);
	if (!!foot)
	{
		FootData = foot->GetData();
	}
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}
