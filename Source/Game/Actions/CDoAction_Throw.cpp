#include "CDoAction_Throw.h"
#include "Global.h"
#include "CAim.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CActionComponent.h"
#include "GameFramework/Character.h"


void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();	// 언리얼의 new 
	Aim->BeginPlay(OwnerCharacter);
}
void ACDoAction_Throw::DoAction()
{
	Super::DoAction();

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
}

void ACDoAction_Throw::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage();

	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::OnAim()
{
	Aim->On();
}

void ACDoAction_Throw::OffAim()
{
	Aim->Off();
}

void ACDoAction_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	Aim->Tick(DeltaTime);
}
