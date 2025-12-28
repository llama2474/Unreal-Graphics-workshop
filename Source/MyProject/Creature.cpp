#include "Creature.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACreature::ACreature()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACreature::BeginPlay()
{
    Super::BeginPlay();
    PeripheralTargetLocation = GetActorLocation();
}

void ACreature::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    if (!CamManager) return;

    FVector CamLoc = CamManager->GetCameraLocation();
    FVector CamForward = CamManager->GetCameraRotation().Vector();
    FVector DirToCreature = (GetActorLocation() - CamLoc).GetSafeNormal();

    float DotValue = FVector::DotProduct(CamForward, DirToCreature);

    UpdateMovementTarget();


    float CurrentSpeed;
    if (DotValue > DetectionThreshold)
    {

        CurrentSpeed = FastEscapeSpeed;
    }
    else
    {

        CurrentSpeed = SlowPeripheralSpeed;
    }

    FVector CurrentLoc = GetActorLocation();
    FVector NewLoc = FMath::VInterpTo(CurrentLoc, PeripheralTargetLocation, DeltaTime, CurrentSpeed);
    SetActorLocation(NewLoc);

    FVector StartLocation = GetActorLocation();
    FVector TargetLocation = CamManager->GetCameraLocation();


    FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);


    FRotator FinalRotation = FRotator(0.0f, LookAtRotation.Yaw, 0.0f);


    SetActorRotation(FinalRotation);
}

void ACreature::UpdateMovementTarget()
{
    APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    if (!CamManager) return;

    FVector CamLoc = CamManager->GetCameraLocation();
    FRotator CamRot = CamManager->GetCameraRotation();

   
    FRotator FlatRot = FRotator(0.0f, CamRot.Yaw, 0.0f);
    FVector OffsetDir = UKismetMathLibrary::GreaterGreater_VectorRotator(FRotator(0, 50.0f, 0).Vector(), FlatRot);

    FVector RawTarget = CamLoc + (OffsetDir * FollowDistance);
    PeripheralTargetLocation = FVector(RawTarget.X, RawTarget.Y, GetActorLocation().Z);
}