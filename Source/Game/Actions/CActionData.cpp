#include "CActionData.h"
#include "Global.h"
#include "CEquipment.h"
#include "GameFramework/Character.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;
	//CEquipment 생성: Character 만 World가 있기에 
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		Equipment->SetData(EquipmentData);	// 얘를 호출하고 BeginPlay 가 나와야 해서
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(GetLabelName(InOwnerCharacter, "Equipment"));
		UGameplayStatics::FinishSpawningActor(Equipment, transform);	// 여기가 진짜위치
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	}	
}
ACEquipment* UCActionData::GetEquipment()
{
	return Equipment;
}
FString UCActionData::GetLabelName(class ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString name;
	name.Append(InOwnerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(InMiddleName);
	name.Append("_");
	name.Append(GetName().Replace(L"DA_",L""));

	return name;
}