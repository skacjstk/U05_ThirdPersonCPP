// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSetViewTarget.generated.h"

UCLASS()
class GAME_API ACSetViewTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSetViewTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Change();
private:
	UPROPERTY(EditInstanceOnly)
		TArray<class ACameraActor*> Cameras;
	uint32 Index;	// 카메라
	UPROPERTY(EditAnyWhere)
		bool bctivation = true;
};
