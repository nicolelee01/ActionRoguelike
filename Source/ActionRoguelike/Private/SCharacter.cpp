// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComp->bUsePawnControlRotation = true; // changes third person camera view (booleans start with b)
    SpringArmComp->SetupAttachment(RootComponent); //
    
    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp); // set camera to spring arm
    
    InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
    GetCharacterMovement()->bOrientRotationToMovement = true; // rotates character to direction we're moving
    bUseControllerRotationYaw = false;
    
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f; // only care about yaw
    
    // GetActorForwardVector returns vector of where actor is currently looking
    AddMovementInput(ControlRot.Vector(), Value);

}

void ASCharacter::MoveRight(float Value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;
    // x: forward (red), y: right (green), z: up (blue)
    FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
    // GetActorForwardVector returns vector of where actor is currently looking
    AddMovementInput(GetActorRightVector(), Value);

}

void ASCharacter::PrimaryAttack()
{
    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
    FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
    if (InteractionComp)
    {
        InteractionComp->PrimaryInteract();
    }
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // movement +1: forward, 0: neutral, -1: backward
    PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
    
    // turning
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    
    // allows user
    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
    
    PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

