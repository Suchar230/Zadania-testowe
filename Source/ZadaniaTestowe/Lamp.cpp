// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"

// Sets default values
ALamp::ALamp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->SetReplicates(true);
	//bReplicates = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point light"));
	LightIntensity = _LightIntensity;
	PointLight->Intensity = LightIntensity;
	PointLight->SetVisibility(false);
	PointLight->SetMobility(EComponentMobility::Movable);
	PointLight->SetLightColor(FLinearColor::Yellow);
	RootComponent = PointLight;

	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light sphere"));
	LightSphereRadius = _LightSphereRadius;
	LightSphere->InitSphereRadius(LightSphereRadius);
	LightSphere->SetupAttachment(RootComponent);
	LightSphere->OnComponentBeginOverlap.AddDynamic(this, &ALamp::OnOverlapBegin);
	LightSphere->OnComponentEndOverlap.AddDynamic(this, &ALamp::OnOverlapEnd);

	ToggleTimer = _ToggleTimer;
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PointLight->bVisible == true)
	{
		if (ToggleTimer >= _ToggleTimer)
		{
			ToggleColor(this->Color);
			ToggleTimer = 0;
		}
		else
		{
			ToggleTimer += DeltaTime;
		}
	}
}

void ALamp::ToggleColor(unsigned int ColorNumber)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Switching color");
	switch (ColorNumber)
	{
	case _Blue:
	{
		PointLight->SetLightColor(FLinearColor::Blue);
		Color++;
		break;
	}
	case _Green:
	{
		PointLight->SetLightColor(FLinearColor::Green);
		Color++;
		break;
	}
	case _Red:
	{
		PointLight->SetLightColor(FLinearColor::Red);
		Color++;
		break;
	}
	case _White:
	{
		PointLight->SetLightColor(FLinearColor::White);
		Color++;
		break;
	}
	case _Yellow:
	{
		PointLight->SetLightColor(FLinearColor::Yellow);
		this->Color = _Blue;
		break;
	}
	}
}
void ALamp::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALamp, PointLight);
	DOREPLIFETIME(ALamp, LightSphere);
	DOREPLIFETIME(ALamp, LightIntensity);
	DOREPLIFETIME(ALamp, LightSphereRadius);
	DOREPLIFETIME(ALamp, ToggleTimer);
	DOREPLIFETIME(ALamp, Color);
}

void ALamp::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		PointLight->SetVisibility(true);
	}
}

void ALamp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		PointLight->SetVisibility(false);
	}
}

