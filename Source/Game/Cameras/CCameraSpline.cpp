#include "CCameraSpline.h"
#include "Global.h"
#include "Components/SplineComponent.h"

ACCameraSpline::ACCameraSpline()
{
	// 에셋 얻어와 저장
	CHelpers::CreateSceneComponent(this, &Spline, "Spline");
	CHelpers::GetAsset<UCurveFloat>(&Curve, "/Game/Enemies/Curve_Dissolve");

}

void ACCameraSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

