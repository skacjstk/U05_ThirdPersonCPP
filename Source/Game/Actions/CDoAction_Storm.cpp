#include "CDoAction_Storm.h"
#include "Global.h"
#include "CAttachment.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"

void ACDoAction_Storm::BeginPlay()
{
	Super::BeginPlay();
	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Storm"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(actor);
			break;
		}
	}
}

void ACDoAction_Storm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	YawAngle += DeltaTime * AroundSpeed;

	if (FMath::IsNearlyEqual(YawAngle, 360.f))
		YawAngle = 0.f;

	FVector center = OwnerCharacter->GetActorLocation();
	FVector awayFromCenter = FVector(Radius, 0, 0);
	FVector rotVector = awayFromCenter.RotateAngleAxis(YawAngle, FVector::UpVector);	// 각도, 회전축

	center += rotVector;
	Box->SetWorldLocation(center);
}

void ACDoAction_Storm::DoAction()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(bActivating);
	bActivating = true;
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Storm::Begin_DoAction()
{
	//파티클 스폰
	YawAngle = OwnerCharacter->GetActorForwardVector().Rotation().Yaw;
	Particle = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, NAME_None);
	Particle->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Particle->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	//충돌체 켜고
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OnCollisions();
	//DPS(0.1초마다 대미지를 주는 함수 -> 타이머로)

	UKismetSystemLibrary::K2_SetTimer(this, "DamageToHittedCharacters", DPS, true);
}

void ACDoAction_Storm::End_DoAction()
{
	Status->SetMove();
	State->SetIdleMode();

	// Todo: 이거 소환 시점에 Begin 이니까 얘도 begin에 들어가는게 맞을지도 모름
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, ActiveTime, false);
}

void ACDoAction_Storm::Abort()
{
	Finish();
}


void ACDoAction_Storm::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Storm::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.Remove(InOtherCharacter);
}

void ACDoAction_Storm::DamageToHittedCharacters()
{
	FDamageEvent e;
	for (int32 i = 0; i < HittedCharacters.Num(); ++i)
	{
		bool bIgnore = false;
		bIgnore |= (HittedCharacters[i] == nullptr);
		bIgnore |= (HittedCharacters[i]->IsPendingKill());

		if (bIgnore)	// 일종의 Null Check 
			continue;

		UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);
		bIgnore |= state->IsDeadMode();

		if (bIgnore)	// 죽었는지
			continue;

		HittedCharacters[i]->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
	}
}

void ACDoAction_Storm::Finish()
{
	//파티클 비활성화
	if(!!Particle)
	Particle->DestroyComponent();

	bActivating = false;

	//충돌체 끄기
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OffCollisions();

	//다단히트 종료: 함수 이름으로 클리어할 수 있음 ( 핸들 없어도 )
	UKismetSystemLibrary::K2_ClearTimer(this, "DamageToHittedCharacters");
}