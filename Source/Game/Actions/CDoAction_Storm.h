// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Storm.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ACDoAction_Storm : public ACDoAction
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Abort() override;
private:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
private:
	UFUNCTION()
		void DamageToHittedCharacters();
	UFUNCTION()
		void Finish();
private:
	UPROPERTY(EditDefaultsOnly)
		float DPS = 0.1f;	// 공격 주기
	UPROPERTY(EditDefaultsOnly)
		float ActiveTime = 5.f;	// 활성화 시간
	UPROPERTY(EditDefaultsOnly)
		float AroundSpeed = 300.f;	// 공전 속도
	UPROPERTY(EditDefaultsOnly)
		float Radius = 150.f;	// 공전 거리

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;
private:
	class UBoxComponent* Box;	// Attachment에 있는 걸 가져와 저장
	bool bActivating;	// 회오리 활성화 여부

	TArray<class ACharacter*> HittedCharacters;
	float YawAngle;	
};
