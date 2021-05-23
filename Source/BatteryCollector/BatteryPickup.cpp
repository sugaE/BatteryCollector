// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
  GetMesh()->SetSimulatePhysics(true);

  // the base power of battery
  BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation() {
  //base pickup
  Super::WasCollected_Implementation();
  //destroy battery
  Destroy();
}

float ABatteryPickup::GetPower(){
  return BatteryPower;
}