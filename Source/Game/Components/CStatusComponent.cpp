// Fill out your copyright notice in the Description page of Project Settings.


#include "CStatusComponent.h"

// Sets default values for this component's properties
UCStatusComponent::UCStatusComponent()
{
}


// Called when the game starts
void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}
