// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// https://docs.unrealengine.com/en-US/API/Runtime/Engine/GameFramework/AGameMode/Tick/index.html
	PrimaryActorTick.bCanEverTick = true;

	// base DecayRate
	DecayRate = 0.01f;

}

void ABatteryCollectorGameMode::BeginPlay(){
	Super::BeginPlay();
	SetCurrentState(EBatteryPlayState::EPlaying);
	// set speed
	ABatteryCollectorCharacter *MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {
		PowerToWin = (MyCharacter->GetInitialPower())*1.25f;
	}

	if(HUDWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if(CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}

}

void ABatteryCollectorGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ABatteryCollectorCharacter *MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(MyCharacter){
		if(MyCharacter->GetCurrentPower() > PowerToWin) {
			SetCurrentState(EBatteryPlayState::EWon);
		}else if (MyCharacter->GetCurrentPower() > 0){
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		} else {
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const {
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState) {
	CurrentState = NewState;
}