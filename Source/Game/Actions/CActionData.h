#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;
	UPROPERTY(EditAnywhere)
		FName StartSection = "";
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;	// LookForward: true라면, 정면 고정, orientRotation을 사용하지 않을 것

};

UCLASS()
class GAME_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
		
public:
	void BeginPlay(class ACharacter* InOwnerCharacter);	// 얘는 BeginPlay가 없어서 직접 만듬;
	
	class ACEquipment* GetEquipment();
private:
	FString GetLabelName(class ACharacter* InOwnerCharacter, FString InMiddleName);
public:
	//Attachment
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;	// 무기 Mesh, Attach 담당

	// Equipment
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;	// 무기 내부 몽타주 담당 
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FLinearColor EquipmentColor;	// 무기에 맞게 마네킹 몸 색 바꾸기 
	
private:
	class ACAttachment* Attachment;	// 실제 객체
	class ACEquipment* Equipment;	// 실제 객체
	

};
