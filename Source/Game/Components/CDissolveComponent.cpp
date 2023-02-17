#include "CDissolveComponent.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

UCDissolveComponent::UCDissolveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 머티리얼 얻어오기.
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "/Game/Textures/Dissolve/M_DissolveEffect_Inst");
	CHelpers::GetAsset<UCurveFloat>(&Curve, "/Game/Enemies/Curve_Dissolve");
}


// Called when the game starts
void UCDissolveComponent::BeginPlay()
{
	Super::BeginPlay();
	// 얻어온 머티리얼로 DynamicMaterial 변환
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);

	// 타입라인 세팅
	FOnTimelineFloat startTimeline;
	startTimeline.BindUFunction(this, "OnStartTimeline");
	Timeline.AddInterpFloat(Curve, startTimeline);
	Timeline.SetPlayRate(PlayRate);
}


// Called every frame
void UCDissolveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
	// ...
}

void UCDissolveComponent::Play()
{
	TimelineFirst = false;
	Timeline.PlayFromStart();
}

void UCDissolveComponent::Stop()
{
	Timeline.Stop();
}

void UCDissolveComponent::OnStartTimeline(float Output)
{
	if (TimelineFirst == false)	// 이 안은 딱 한번만 실행되게
	{
//		TArray<UActorComponent*> components = GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass());
//		
//		// 무기까지 바꾸고 싶다면 GetOwnerChildern() ㄱㄱ 
//		for (UActorComponent* component : components)
//		{
//			UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(component);	// 프리미티브는 머티리얼을 가질 수 있음
//			if (!!primitive)
//			{
//				for (int32 i = 0; i < primitive->GetNumMaterials(); ++i)
//					primitive->SetMaterial(i, DynamicMaterial);
//			}
//		}

		ACharacter* character = Cast<ACharacter>(GetOwner());
		CheckNull(character);

		character->GetMesh()->SetMaterial(0, DynamicMaterial);
		character->GetMesh()->SetMaterial(1, DynamicMaterial);	// 여기서 터진다.

		TimelineFirst = true;
	}	// 머티리얼을 DynamicMaterial 로 바꾸는 코드 

	DynamicMaterial->SetScalarParameterValue("amount", Output);
}