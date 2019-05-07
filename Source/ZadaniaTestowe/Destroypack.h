// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine.h"
#include "UnrealNetwork.h" 
#include "DestructibleComponent.h"
#include "Destroypack.generated.h"

constexpr float _DamageValue = 10.f;
constexpr float _ImpulseValue = 10.f;
constexpr int _MaxHealth = 50;

UCLASS()
class ZADANIATESTOWE_API ADestroypack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestroypack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	UFUNCTION()
	void Trigger(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Replicated, Category = "DestructibleComponent")
	UDestructibleComponent* DestructibleComponent;

	UPROPERTY(EditAnywhere, Replicated, Category = "StaticComponent")
	UStaticMeshComponent* StaticComponent;

	UPROPERTY(EditAnywhere, Replicated, Category = "IsDestroyed")
	bool IsDestroyed;

	UPROPERTY(EditAnywhere, Replicated, Category = "Health")
	int Health;

	UPROPERTY(EditAnywhere, Category = "DamageValue")
	float DamageValue;

	UPROPERTY(EditAnywhere, Category = "ImpulseValue")
	float ImpulseValue;
};
