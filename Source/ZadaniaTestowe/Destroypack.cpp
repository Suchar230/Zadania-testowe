// Fill out your copyright notice in the Description page of Project Settings.

#include "Destroypack.h"

// Sets default values
ADestroypack::ADestroypack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene component"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible component"));
	DestructibleComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision); // doesn't work properly
	DestructibleComponent->SetupAttachment(RootComponent); 
	DestructibleComponent->SetSimulatePhysics(false);
	DestructibleComponent->SetVisibility(true);

	StaticComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static component"));
	StaticComponent->SetupAttachment(RootComponent);
	StaticComponent->SetVisibility(true);
	StaticComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	StaticComponent->OnComponentHit.AddDynamic(this, &ADestroypack::Trigger);

	IsDestroyed = false;
	DamageValue = _DamageValue;
	ImpulseValue = _ImpulseValue;
	Health = _MaxHealth;
}

// Called when the game starts or when spawned
void ADestroypack::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestroypack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADestroypack::Trigger(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsDestroyed && Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Object is being destroyed.");
		StaticComponent->SetVisibility(false);
		StaticComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		DestructibleComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics); // doesn't work properly
		DestructibleComponent->SetSimulatePhysics(true);
		DestructibleComponent->SetVisibility(true);
		IsDestroyed = true;
		DestructibleComponent->ApplyDamage(this->DamageValue, Hit.Location, NormalImpulse, this->ImpulseValue);
	}
	else if (Health > 0)
	{
		Health--;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Health:" + FString::FromInt(Health));
	}
}

void ADestroypack::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADestroypack, DestructibleComponent);
	DOREPLIFETIME(ADestroypack, StaticComponent);
	DOREPLIFETIME(ADestroypack, Health);
	DOREPLIFETIME(ADestroypack, IsDestroyed);
}
