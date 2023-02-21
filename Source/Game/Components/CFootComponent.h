// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CFootComponent.generated.h"

USTRUCT(BlueprintType)
struct FFootData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance;	//왼발 거리
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance;	//오른발 거리

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance;	//골반 거리
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float LeftAlpha;	//왼발 알파
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float RightAlpha;	//오른발 알파
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCFootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCFootComponent();
	
	FORCEINLINE const FFootData& GetData() { return Data; }
	FORCEINLINE bool IsIK() { return bActive; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Trace(FName& InSocketName, float& OutDistance, FRotator& OutRotation);	// 발이 얼마만큼 떨어져 있는지 
		
	UFUNCTION()
		void OnActorBeginOverlap(AActor* overlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnActorEndOverlap(AActor* overlappedActor, AActor* OtherActor);
	// 소켓 이름 
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		FName LeftFootSocket = "Foot_L";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		FName RightFootSocket = "Foot_R";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
	float AdditionalDistance = 55.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForOneFrame;	// 전역공간의 Enum은 바이트를 알려줄 필요가 있다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		float OffsetDistance = 5.0f;	// 발목 Offset Distance
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		float InterpSpeed = 20.f;	// n분의 1초만에 
private:
	class ACharacter* OwnerCharacter;
	float CapsuleHalfHeight;
	float StepHeight;
	FFootData Data;
	bool bActive = false;
};
