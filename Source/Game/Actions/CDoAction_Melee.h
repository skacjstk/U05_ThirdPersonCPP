// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

// Todo: 여기부터
UCLASS()
class GAME_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

	virtual void DoAction()			override;
	virtual void Begin_DoAction()	override;
	virtual void End_DoAction()		override;
};
