// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CDissolveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCDissolveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCDissolveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Play();
	void Stop();	// 타임라인 중지: End_Dead() 때 호출

private:
	UFUNCTION()
		void OnStartTimeline(float Output);
private:
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstanceConstant* Material;
	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* Curve;
	class UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(EditDefaultsOnly)
		float PlayRate = 0.3f;
	FTimeline Timeline; 
	
	bool TimelineFirst = false;
		
};
