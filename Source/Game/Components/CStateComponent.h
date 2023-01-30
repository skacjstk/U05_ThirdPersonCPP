// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Roll, BackStep, Equip, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetIdleMode();
	void SetRollMode();
	void SetBackStepMode();
	void SetEquipMode();

	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsRollMode() { return Type == EStateType::Roll; }
	FORCEINLINE bool IsBackMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }

private:
	void ChangeType(EStateType InNewType);

	// Field
public:
	UPROPERTY(BlueprintAssignable)	// BP 이벤트 꽂을 수 있음
		FStateTypeChanged OnStateTypeChanged;
private:
	EStateType Type;
};
