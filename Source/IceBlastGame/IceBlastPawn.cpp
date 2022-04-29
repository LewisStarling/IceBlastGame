// Fill out your copyright notice in the Description page of Project Settings.


#include "IceBlastPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "IceBlastGameGameMode.h"



// Sets default values
AIceBlastPawn::AIceBlastPawn()
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
void AIceBlastPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Ice->OnComponentHit.AddDynamic(this, &AIceBlastPawn::OnHit);
	Ice->OnComponentBeginOverlap.AddDynamic(this, &AIceBlastPawn::OnBeginOverlap);
	GameMode = Cast<AIceBlastGameGameMode>(GetWorld()->GetAuthGameMode());

	bGameEnded = false;
	Mass = Ice->GetMass();
	bJump = false;
	DefaultSideForce = SideForce;
	
	
}

// Called every frame
void AIceBlastPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;
	Zvelocity = GetVelocity().Z;
	Yvelocity = GetVelocity().Y;
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("Output: %f"), SideForce));

	if (Zvelocity > 2 || Zvelocity < -2) // is character in the air?
	{ 
		bJump = true;
		SideForce = 0;
	}
	else
	{	
		bJump = false;
		SideForce = DefaultSideForce;
	}

}

// Called to bind functionality to input
void AIceBlastPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIceBlastPawn::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AIceBlastPawn::Jump);
}

void AIceBlastPawn::OnHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AIceBlastPawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AIceBlastPawn::GameEnded()
{

}

void AIceBlastPawn::EndGame()
{

}

void AIceBlastPawn::MoveRight(float AxisValue)
{
	if(bGameEnded)
	
	return; 

	if(bPause)

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
		//GEngine->AddOnScreenDebugMessage(-1, -5.f, FColor::Red,"FireElse");
	}
}

void AIceBlastPawn::Jump()
{
	if(!bJump)
	{
		YvelocityBeforeJump = Yvelocity;
		FVector Impulse = FVector(0.0f, 0.0f, JumpHeight);
		Ice->AddImpulse(Impulse, "", true);
	}

}

void AIceBlastPawn::OnLanded()
{
	SideForce = DefaultSideForce;	
}

void AIceBlastPawn::AddSlide()
{
	FVector Impulse = FVector(0.0f, YvelocityBeforeJump, -0.0f);
	Ice->AddImpulse(Impulse, "", true);
	YvelocityBeforeJump = 0.0f;
}

void AIceBlastPawn::StopForce()
{
	bPause = true;
}

void AIceBlastPawn::StartForce()
{
	bPause = false;
}