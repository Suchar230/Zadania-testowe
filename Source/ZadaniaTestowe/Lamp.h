// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Engine.h"
#include "UnrealNetwork.h" 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

enum ColorEnum { _Blue, _Green, _Red, _White, _Yellow };
constexpr float _LightIntensity = 3000.f;
constexpr float _LightSphereRadius = 300.f;
constexpr float _ToggleTimer = 1.f;

UCLASS()
class ZADANIATESTOWE_API ALamp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "PointLight")
	UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "LightSphere")
	USphereComponent* LightSphere;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "LightIntensity")
	float LightIntensity;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "LightSphereRadius")
	float LightSphereRadius;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ToggleTimer")
	float ToggleTimer;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ColorChangeTimer")
	unsigned int Color;

	UFUNCTION()
	void ToggleColor(unsigned int ColorNumber);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

