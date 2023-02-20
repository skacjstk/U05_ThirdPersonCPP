#include "CFootComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UCFootComponent::UCFootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UCFootComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	StepHeight = OwnerCharacter->GetCharacterMovement()->MaxStepHeight;
}


void UCFootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance;
	FRotator leftRotation;
	Trace(LeftFootSocket, leftDistance, leftRotation);
	float rightDistance;
	FRotator rightRotation;
	Trace(RightFootSocket, rightDistance, rightRotation);

	// 로컬 공간 ( 위아래가 X임 )



	float offset = FMath::Min(leftDistance, rightDistance);	// 둘중 누가 떠있는놈인지 저장
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, leftDistance - offset, DeltaTime, InterpSpeed);	// 로컬공간에선 x가 위아래라서, X를 기준삼는다.
	//F는 벡터 전용, R 은 회전 전용
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(rightDistance - offset), DeltaTime, InterpSpeed);

	// World 공간 ( Z축을 사용하면 된다 ) // AddTransform 사용할 것
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);	// World 니까 자신을 뺄 필요가 없지

	Data.LeftRotation = leftRotation;
	Data.RightRotation = rightRotation;

	// 레그 IK에 사용할 알파 값
	// StepHeight 가져오기는 BeginPlay에 있음.




	
	if (!FMath::IsNearlyZero(leftDistance, rightDistance))
	{
		if (leftDistance > rightDistance)
		{
			Data.LeftAlpha = Data.LeftDistance.X / StepHeight;
			Data.RightAlpha = -(Data.RightDistance.X + OffsetDistance) / StepHeight;
		}
		else
		{
			Data.LeftAlpha = (Data.LeftDistance.X - OffsetDistance) / StepHeight;
			Data.RightAlpha = -Data.RightDistance.X / StepHeight;
		}
	}



}

void UCFootComponent::Trace(FName& InSocketName, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.f;
	OutRotation = FRotator::ZeroRotator;
	FVector socketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InSocketName);
	FVector start = FVector(socketLocation.X, socketLocation.Y, OwnerCharacter->GetActorLocation().Z);

	float traceZ = start.Z - CapsuleHalfHeight - AdditionalDistance;	// 허리에 반까지 
	FVector end = FVector(socketLocation.X, socketLocation.Y, traceZ);

	TArray<AActor*> ignores;

	FHitResult hitResult;
	ignores.Add(OwnerCharacter);
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		ignores,
		DrawDebugType,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	);

	CheckFalse(hitResult.IsValidBlockingHit());

	// 지면이 충돌된 지점까지의 거리 구하기
	float underGround = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();	// 충돌위치 - Trace 끝부분
	OutDistance = OffsetDistance + underGround - AdditionalDistance;

	OutRotation.Roll = UKismetMathLibrary::DegAtan2(hitResult.ImpactNormal.Y, hitResult.ImpactNormal.Z);
	OutRotation.Pitch = -UKismetMathLibrary::DegAtan2(hitResult.ImpactNormal.X, hitResult.ImpactNormal.Z);

}

