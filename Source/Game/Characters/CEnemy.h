#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Components/CStateComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "CEnemy.generated.h"

UCLASS()
class GAME_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void ChangeColor(FLinearColor InColor) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);
	virtual void Hitted() override;
	virtual void Dead() override;

	UFUNCTION()
		 virtual void End_Dead() override;
	UFUNCTION()
		void RestoreLogoColor();
protected:
	//	위젯
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCActionComponent* Action;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;


	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCDissolveComponent* Dissolve;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	UPROPERTY(EditAnywhere)
		ESlateVisibility VisibleType = ESlateVisibility::Hidden;
	UPROPERTY(EditAnywhere)
		float DeadLaunchValue = 100000.f;
	UPROPERTY(EditAnywhere)
		float LaunchValue = 25.f;	// 밀려나는 고유값
	float DamageValue;
	AActor* Causer;
	ACharacter* Attacker;
};
