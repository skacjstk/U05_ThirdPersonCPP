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

	Health	= MaxHealth;
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
void UCStatusComponent::IncreaseHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

}
void UCStatusComponent::DecreaseHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}
