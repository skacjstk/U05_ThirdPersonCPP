// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlp, class ACharacter*, InAttacker, class AActor*, InCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlp, class ACharacter*, InAttacker, class AActor*, InCauser, class ACharacter*, InOtherCharacter);

UCLASS()
class GAME_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void OnCollisions(FString InCollisionName = "None");	// 노티파이 함수
	void OffCollisions();

	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip(); 
	UFUNCTION(BlueprintImplementableEvent)	// 우리 Equipment Delegate 가 이런 타입
		void OnUnequip();

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
// 필드

public:
	UPROPERTY(BlueprintAssignable)
		FAttachmentBeginOverlp OnAttachmentBeginOverlap;
	UPROPERTY(BlueprintAssignable)
		FAttachmentEndOverlp OnAttachmentEndOverlap;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

private:
	TArray<class UShapeComponent*> ShapeComponents;	// 무기 충돌체 들
};
