// FPSPistol.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSPistol.generated.h"

UCLASS()
class WINTERSTEALTHFPS_API AFPSPistol : public AActor
{
	GENERATED_BODY()

public:
	AFPSPistol();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Mesh for the pistol
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GunMesh;

	// Collision to detect player proximity
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* PickupCollision;
};
