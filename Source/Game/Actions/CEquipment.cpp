#include "CEquipment.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"

ACEquipment::ACEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEquipment::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!!OwnerCharacter) {
		State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
		Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	}	
}

void ACEquipment::Equip_Implementation()
{
	// 장착몽타주 재생
	// 상태 equip

	State->SetEquipMode();

	if(!!Data.AnimMontage)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	else 
	{
		Begin_Equip();
		End_Equip();
	}
}

void ACEquipment::Begin_Equip_Implementation()
{	
	// 델리게이트 콜 (소켓 Attach)
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	State->SetIdleMode();
}

void ACEquipment::Unequip_Implementation()
{

}
