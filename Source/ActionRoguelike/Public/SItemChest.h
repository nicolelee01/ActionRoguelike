// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
    // need _Implementation as boilerplate from ISGameplayInterface.h Interact fn
public:
    // expose value
    UPROPERTY(EditAnywhere)
    float TargetPitch;
    
    void Interact_Implementation(APawn* InstigatorPawn);

protected:
    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;
    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LidMesh;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //Sets default values for this actor's properties
    ASItemChest();
};
