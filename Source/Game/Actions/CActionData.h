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
		class UAnimMOntage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;
	UPROPERTY(EditAnywhere)
		FName StartSection = "";
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;	// true라면, 정면 고정, orientRotation을 사용하지 않을 것

};

UCLASS()
class GAME_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FLinearColor EquipmentColor;	// 무기에 맞게 마네킹 몸 색 바꾸기 
	
};
