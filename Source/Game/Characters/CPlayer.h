#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "ICharacter.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class GAME_API ACPlayer : public ACharacter, public IICharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	FORCEINLINE class UCUserWidget_ActionContainer* GetActionContainerWidget() { return ActionContainerWidget; }
private:
	// SceneComponent
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
	// ActorComponent
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
	class UCMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = 0;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCUserWidget_ActionContainer> ActionContainerWidgetClass;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FGenericTeamId GetGenericTeamId() const override;	// Interface 재정의 

private:
	void BindActionItem();
	//Axis Mapping
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnZoom(float InAxis);

	// Action Mapping
	void OnEvade();
	void OnWalk();
	void OffWalk();

	
	UFUNCTION()	void OnFist();
	UFUNCTION()	void OnOneHand();
	UFUNCTION()	void OnTwoHand();
	UFUNCTION()	void OnMagicBall();
	UFUNCTION()	void OnWarp();
	UFUNCTION()	void OnStorm();

	void OnDoAction();

	void OnAim();	// 우클릭
	void OffAim();

	void OnActionSwitch();
	void OffActionSwitch();

private:
	void Begin_Roll();
	void Begin_BackStep();
public:
	void End_Roll();
	void End_BackStep();	// 거의 notify 호출 

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// IICharacter을(를) 통해 상속됨
	virtual void Hitted() override;
	virtual void Dead() override;
	virtual void End_Dead() override;
	virtual void ChangeColor(FLinearColor InColor);
private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);	
	// CStateComponent에 OnStateTypeChanged에 바인딩
	float DamageValue;
	AActor* Causer;
	ACharacter* Attacker;

	class UCUserWidget_ActionContainer* ActionContainerWidget;
};
