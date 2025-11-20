// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/DestructibleObjectActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Projectile/FPSProjectile.h"

// Sets default values
ADestructibleObjectActor::ADestructibleObjectActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and setup mesh
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));

    // Bind OnHit to handle projectile collisions
    MeshComponent->OnComponentHit.AddDynamic(this, &ADestructibleObjectActor::OnHit);
}

// Called when the game starts or when spawned
void ADestructibleObjectActor::BeginPlay()
{
    Super::BeginPlay();
}

void ADestructibleObjectActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// When hit by projectile
void ADestructibleObjectActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor->IsA(AFPSProjectile::StaticClass()))
    {

        // Destroy the object
        Destroy();

        // Optional: destroy the projectile too
        OtherActor->Destroy();
    }
}
