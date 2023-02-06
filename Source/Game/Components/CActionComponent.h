#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, MagicBall, Storm, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCActionData* GetCurrent() { return Datas[(int32)Type]; }
public:
	//ActionType Is 
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::OneHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { return Type == EActionType::Warp; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMagicBallMode() { return Type == EActionType::MagicBall; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsStormMode() { return Type == EActionType::Storm; }
public:
	// ActionType Set
	void SetUnarmedMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetWarpMode();
	void SetMagicBallMode();
	void SetStormMode();

	void DoAction();

	void DoOnAim();		// 우클릭 누르기
	void DoOffAim();	// 우클릭 떼기

	//	사망 시 충돌체 끄기 외 사망했을 때 했어야 할 일을 호출 (컴포넌트 속 has 관계 아이템 제거 등)
	void Dead();
	void End_Dead();

	void OffAllCollisions();
private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

	// 필드
public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;
private:
	EActionType Type;
private:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* Datas[(int32)EActionType::Max];	// 실제 눈에 보이는 데이터: 세팅값 포함 

};
