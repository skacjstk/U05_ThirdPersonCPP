#include "CCameraActor.h"
#include "Global.h"
#include "CCameraSpline.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"

ACCameraActor::ACCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Camera, "Camera");

}

void ACCameraActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACCameraSpline::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		if (actor->IsA<ACCameraSpline>() && actor->GetName().Contains("BP_CCameraSpline"))
		{
			Spline = Cast<ACCameraSpline>(actor);
		}

	}
}

void ACCameraActor::OnBeginOverlap()
{
	FOnTimelineFloat progress;
	progress.BindUFunction(this, "OnPlay");

	FOnTimelineEvent finish;
	finish.BindUFunction(this, "OnFinish");

	Timeline.AddInterpFloat(Spline->GetCurve(), progress);
	Timeline.SetTimelineFinishedFunc(finish);	// 타임라인이 끝났을 때의  함수 바인딩
	Timeline.SetPlayRate(PlayRate);

	Timeline.PlayFromStart();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	controller->SetViewTarget(this);
}

void ACCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
}

void ACCameraActor::OnPlay(float Output)
{
	USplineComponent* spline = Spline->GetSpline();

	FVector location = spline->GetLocationAtDistanceAlongSpline(spline->GetSplineLength() * Output, ESplineCoordinateSpace::World);
	FRotator rotator = spline->GetRotationAtDistanceAlongSpline(spline->GetSplineLength() * Output, ESplineCoordinateSpace::World);

	SetActorLocation(location);
	SetActorRotation(rotator);

}

void ACCameraActor::OnFinish()
{
	Timeline.Stop();
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(player);
	controller->SetViewTarget(player);

}

