#include "CSetViewTarget.h"
#include "Global.h"
#include "Camera/CameraActor.h"

ACSetViewTarget::ACSetViewTarget()
{

}

// Called when the game starts or when spawned
void ACSetViewTarget::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::K2_SetTimer(this, "Change", 2.f, true);

//	TArray<AActor*> actors;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), actors);
//	
//	for (AActor* actor : actors)
//	{
//		ACameraActor* camera = Cast<ACameraActor>(actor);
//		if (!!camera)
//			Cameras.Add(camera);
//	}

}

void ACSetViewTarget::Change()
{
	CheckFalse(bctivation);
	// 0. PlayerCameraManager 불러오기


	if (false)
	{
		// 1. 확 바꾸기
		APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		CheckNull(cameraManager);
		CheckTrue(Cameras.Num() < 1);

		cameraManager->SetViewTarget(Cameras[Index++]);
		Index = Index % Cameras.Num();
	}
	else
	{
		// 2. 천천히 바꾸기
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		CheckNull(controller);
		CheckTrue(Cameras.Num() < 1);

		controller->SetViewTargetWithBlend(Cameras[Index++], 2.f, EViewTargetBlendFunction::VTBlend_EaseIn, 2.f); //바뀌는게 걸리는 시간
		Index %= Cameras.Num();
	}

}
