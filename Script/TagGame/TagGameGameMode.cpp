// Copyright Epic Games, Inc. All Rights Reserved.

#include "TagGameGameMode.h"
#include "TagGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Ball.h"
#include "Engine/TargetPoint.h"

ATagGameGameMode::ATagGameGameMode()
{
	// set default pawn class to our Blueprinted character
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATagGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	ResetMatch();
}

void ATagGameGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < GameBalls.Num(); i++)
	{
		if (GameBalls[i]->GetAttachParentActor() != GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			return;
		}
	}

	for (int32 i = 0; i < GameBalls.Num(); i++)
	{
		if (GameBalls[i]->GetAttachParentActor() == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			GameBalls[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
	}
	ResetMatch();
}

const TArray<class ABall*>& ATagGameGameMode::GetBalls() const
{
	return GameBalls;
}

void ATagGameGameMode::ResetMatch()
{
	TargetPoints.Empty();
	GameBalls.Empty();

	for (TActorIterator<ATargetPoint> It(GetWorld()); It; ++It)
	{
		TargetPoints.Add(*It);
	}

	for (TActorIterator<ABall> It(GetWorld()); It; ++It)
	{
		if (It->GetAttachParentActor())
		{
			It->AttachToActor(nullptr, FAttachmentTransformRules::KeepWorldTransform);
		}

		GameBalls.Add(*It);
	}

	for (int32 i = 0; i < GameBalls.Num(); i++)
	{
		const int32 RandomTargetIndex = FMath::RandRange(0, TargetPoints.Num() - 1);
		GameBalls[i]->SetActorLocation(TargetPoints[RandomTargetIndex]->GetActorLocation());
		TargetPoints.RemoveAt(RandomTargetIndex);
	}
}
