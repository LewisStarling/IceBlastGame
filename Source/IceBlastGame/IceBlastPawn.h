// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IceBlastPawn.generated.h"

UCLASS()
class ICEBLASTGAME_API AIceBlastPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIceBlastPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// UPROPERTYS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	USkeletalMeshComponent* Ice;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Floats", meta = (ToolTip = "How fast the player goes, dependent of friction"))
	float SideForce;

	UPROPERTY(EditAnywhere, Category = "Floats", meta = (ToolTip = "The Higher The Value, The More Slide (Between 0-1)"))
	float ReducedSpeed;

	UPROPERTY(EditAnywhere, Category = "Floats")
	float JumpHeight;

	class AIceBlastGameGameMode* GameMode;
	
	bool bGameEnded;
	float Mass;
	float DeltaSeconds;
	float CurrentAxisValue;
	bool bJump;
	float DefaultSideForce;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnLanded();

	UFUNCTION(BlueprintCallable)
	void SetSideForce();
	
	//Functions
	void GameEnded();
	void MoveRight(float AxisValue);
	void EndGame();
	void Jump();
	void StopJump();
	

private:

};
