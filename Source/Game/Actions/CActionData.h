#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

/*
@ struct Equipment
*/
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

/*
@ struct DoAction
*/
USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float Power = 1.f;
	UPROPERTY(EditAnywhere)
		float HitStop;	// 멈칫 시간 
	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;
	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;
	UPROPERTY(EditAnywhere)
		FString SpecificCollisionName = L"None";
};

UCLASS()
class GAME_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
		
public:
	void BeginPlay(class ACharacter* InOwnerCharacter);	// 얘는 BeginPlay가 없어서 직접 만듬;
public:
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }
private:
	FString GetLabelName(class ACharacter* InOwnerCharacter, FString InMiddleName);
public:
	//Attachment
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attachment")
		TSubclassOf<class ACAttachment> AttachmentClass;	// 무기 Mesh, Attach 담당

	// Equipment
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEquipment> EquipmentClass;	// 무기 내부 장착 몽타주 담당 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FLinearColor EquipmentColor;	// 무기에 맞게 마네킹 몸 색 바꾸기 

	// DoAction
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;	// 무기 내부 공격 몽타주 및 데미지 담당
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;
	
private:	// 실제 객체
	class ACAttachment* Attachment;
	class ACEquipment* Equipment;	
	class ACDoAction* DoAction;		
	

};
