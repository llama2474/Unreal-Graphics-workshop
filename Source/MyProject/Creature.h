#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

UCLASS()
class MYPROJECT_API ACreature : public ACharacter
{
    GENERATED_BODY()

public:
    ACreature();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature Settings")
    float DetectionThreshold = 0.85f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature Settings")
    float FollowDistance = 1800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature|Movement")
    float SlowPeripheralSpeed = 4.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature|Movement")
    float FastEscapeSpeed = 25.0f;  

private:
    FVector PeripheralTargetLocation;
    void UpdateMovementTarget();
};