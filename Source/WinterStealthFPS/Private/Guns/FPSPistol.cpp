// FPSPistol.cpp

#include "Guns/FPSPistol.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AFPSPistol::AFPSPistol()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create collision sphere
	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollision"));
	PickupCollision->InitSphereRadius(50.f);
	RootComponent = PickupCollision;

	// Create gun mesh
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent);

	// Optional: assign a mesh from the engine if you haven’t yet set one in Blueprint
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GunAsset(TEXT("/Engine/BasicShapes/Cube")); // replace later
	if (GunAsset.Succeeded())
	{
		GunMesh->SetStaticMesh(GunAsset.Object);
	}
}

void AFPSPistol::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
