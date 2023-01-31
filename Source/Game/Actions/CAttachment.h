// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

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
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip(); 
	UFUNCTION(BlueprintImplementableEvent)	// 우리 Equipment Delegate 가 이런 타입
		void OnUnequip();


protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

// 필드
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
};
