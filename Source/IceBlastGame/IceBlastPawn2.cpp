// Fill out your copyright notice in the Description page of Project Settings.


#include "IceBlastPawn2.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "IceBlastGameGameMode.h"

// Sets default values
AIceBlastPawn2::AIceBlastPawn2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ice = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Ice"));
	RootComponent = Ice;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
 	SpringArm->SetupAttachment(Ice);

	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	Ice->BodyInstance.bLockXRotation = true;
	Ice->BodyInstance.bLockYRotation = true;
	Ice->BodyInstance.bLockZRotation = true;

	SideForce = 100;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AIceBlastPawn2::BeginPlay()
{
	Super::BeginPlay();
	
	Ice->OnComponentHit.AddDynamic(this, &AIceBlastPawn2::OnHit);
	Ice->OnComponentBeginOverlap.AddDynamic(this, &AIceBlastPawn2::OnBeginOverlap);
	GameMode = Cast<AIceBlastGameGameMode>(GetWorld()->GetAuthGameMode());

	bGameEnded = false;
	Ice->SetSimulatePhysics(true);
	Mass = Ice->GetMass();
	bJump = false;
	DefaultSideForce = SideForce;
}

// Called every frame
void AIceBlastPawn2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;
}

// Called to bind functionality to input
void AIceBlastPawn2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AIceBlastPawn2::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AIceBlastPawn2::Jump);
}

void AIceBlastPawn2::OnHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AIceBlastPawn2::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AIceBlastPawn2::GameEnded()
{

}

void AIceBlastPawn2::EndGame()
{

}

void AIceBlastPawn2::MoveRight(float AxisValue)
{
	if(bGameEnded)
	
	return; 
	
	if(AxisValue != 0)
	{
		FVector Impulse = FVector(0.0f, Mass * SideForce * DeltaSeconds * AxisValue, 0.0f);
		Ice->AddImpulse(Impulse, "", true);
		CurrentAxisValue = AxisValue; 
	}
	else 
	{
		FVector Impulse = FVector(0.0f, Mass * SideForce * ReducedSpeed * DeltaSeconds * CurrentAxisValue, 0.0f);
		Ice->AddImpulse(Impulse, "", true);
	}
}

void AIceBlastPawn2::Jump()
{
	if(!bJump)
	{
		SetSideForce();
		bJump = true;
		FVector Impulse = FVector(0.0f, 0.0f, JumpHeight);
		Ice->AddImpulse(Impulse, "", true);
	}

	
}

void AIceBlastPawn2::OnLanded()
{
	bJump = false;
	SideForce = DefaultSideForce;
}

void AIceBlastPawn2::SetSideForce()

{
	SideForce = 0.0;
}
	PlayerInputComponent->BindAxis("MoveRight", this, &AIceBlastPawn2::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AIceBlastPawn2::Jump);
}

void AIceBlastPawn2::OnHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AIceBlastPawn2::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AIceBlastPawn2::GameEnded()
{

}

void AIceBlastPawn2::EndGame()
{

}

void AIceBlastPawn2::MoveRight(float AxisValue)
{
	if(bGameEnded)
	
	return; 
	
	if(AxisValue != 0)
	{
		FVector Impulse = FVector(0.0f, Mass * SideForce * DeltaSeconds * AxisValue, 0.0f);
		Ice->AddImpulse(Impulse, "", true);
		CurrentAxisValue = AxisValue; 
	}
	else 
	{
		FVector Impulse = FVector(0.0f, Mass * SideForce * ReducedSpeed * DeltaSeconds * CurrentAxisValue, 0.0f);
		Ice->AddImpulse(Impulse, "", true);
	}
}

void AIceBlastPawn2::Jump()
{
	if(!bJump)
	{
		SetSideForce();
		bJump = true;
		FVector Impulse = FVector(0.0f, 0.0f, JumpHeight);
		Ice->AddImpulse(Impulse, "", true);
	}

	
}

void AIceBlastPawn2::OnLanded()
{
	bJump = false;
	SideForce = DefaultSideForce;
}

void AIceBlastPawn2::SetSideForce()

{
	SideForce = 0.0;
}



