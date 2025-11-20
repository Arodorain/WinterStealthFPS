// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::BulletPhysic);

		RootComponent = CollisionComponent;
	}

	if (!ProjectileMeshComponent) {
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

		// 1. Setup an imported mesh
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Asset/Projectile/Sphere.Sphere"));

		// 2. Get assets from Unreal
		//static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));

		if (ProjectileMeshAsset.Succeeded()) {
			ProjectileMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object);
		}

		// Setting up material for sphere
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> ProjectileMaterialAsset(TEXT("/Game/Asset/fp-arms/textures/arms_Mat.arms_Mat"));
		if (ProjectileMaterialAsset.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(ProjectileMaterialAsset.Object, this);
		}

		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	if (!ProjectileMovementComponent) {
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = BulletSpeed;
		ProjectileMovementComponent->MaxSpeed = BulletSpeed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;

		ProjectileMovementComponent->bShouldBounce = true;

		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	InitialLifeSpan = 3.0f; // Unity Destory (3.0f)
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection) // (1,0,0)
{
	// 1. FVector ShootDirection: Pass by value, leaset effecient, Basiclly just duplicating the data and giving it to you
	// 2. FVector* ShootDirection: Pass pointer memory, efficient cus memory adress. But neeed to derefernce the pointer to get the value
	// 3. FVector& ShootDirection: Pass by reference, efficent and easy to use. Just like a normal varible or think of it as a out
	// 4. const FVector& ShootDirection: Pass by reference but read only, efficient and safe to use

	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * ShootDirection;
}

void AFPSProjectile::BulletPhysic(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherComponent && OtherComponent->IsSimulatingPhysics())
		{
			// Apply a strong impulse so it visibly moves
			OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 50.0f, Hit.ImpactPoint);
		}

		// Delay destruction slightly so the impulse can take effect
		SetLifeSpan(0.05f);
	}
}

