// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleObjectActor.generated.h"

UCLASS()
class WINTERSTEALTHFPS_API ADestructibleObjectActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADestructibleObjectActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // The mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
    UStaticMeshComponent* MeshComponent;

    // Called when hit by projectile
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
