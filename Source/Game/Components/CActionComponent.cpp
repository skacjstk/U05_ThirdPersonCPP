#include "CActionComponent.h"
#include "Global.h"
#include "Actions/CEquipment.h"
#include "Actions/CActionObjectContainer.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction.h"
#include "GameFramework/Character.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* charcater = Cast<ACharacter>(GetOwner());
	for (int i = 0; i < (int32)EActionType::Max; ++i)
	{
		if(!!Datas[i])
			Datas[i]->BeginPlay(charcater);
	}
}

void UCActionComponent::SetUnarmedMode()
{
	if(!!Datas[(int32)Type] && Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment()->Unequip();

	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetStormMode()
{
	SetMode(EActionType::Storm);
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* doAction = Datas[(int32)Type]->GetDoAction();

		if (!!doAction)
			doAction->DoAction();
	}
}

void UCActionComponent::DoOnAim()
{
	if (!!Datas[(int32)Type])
	{
		ACDoAction* doAction = Datas[(int32)Type]->GetDoAction();

		if (!!doAction)
			doAction->OnAim();
	}
}

void UCActionComponent::DoOffAim()
{
	if (!!Datas[(int32)Type])
	{
		ACDoAction* doAction = Datas[(int32)Type]->GetDoAction();

		if (!!doAction)
			doAction->OffAim();
	}
}

void UCActionComponent::SetMode(EActionType InNewType)
{	
	if (Type == InNewType)
	{
		SetUnarmedMode();	// Unarmed는 전용이 따로 있음 
		return;
	}
	else if (IsUnarmedMode() == false)	// 다른 무기 누르면 해제와 장착을 
	{
		CLog::Print((int32)InNewType);

		if (!!Datas[(int32)Type] && Datas[(int32)Type]->GetEquipment())
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}
	
	if (!!Datas[(int32)InNewType] && Datas[(int32)InNewType]->GetEquipment())
		Datas[(int32)InNewType]->GetEquipment()->Equip();
	
	ChangeType(InNewType);
	// Todo. 노티파이
	// Todo. 원핸드 꺼내고 폰 컨트롤 켜기
	// Todo. 구르거나 백스텝 버그 수정 
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;
	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

void UCActionComponent::Dead()
{
	OffAllCollisions();
}

void UCActionComponent::End_Dead()
{
	// Tod. All Attachment, Equipment, DoAction Release
}

void UCActionComponent::OffAllCollisions()
{
	for (const auto& data : Datas) 
	{
		if (data == nullptr || data->GetAttachment() == nullptr)
			continue;
		data->GetAttachment()->OffCollisions();
	}
}
