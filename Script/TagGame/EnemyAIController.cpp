// Fill out your copyright notice in the Description page of Project Settings.





#include "EnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "TagGameGameMode.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UseBlackboard(BlackboardData, BlackboardComponent))
	{
		BlackboardComponent->SetValueAsObject(PlayerKey, GetWorld()->GetFirstPlayerController()->GetPawn());
	}
	static APawn* PlayerPawn = Cast<APawn>(BlackboardComponent->GetValueAsObject(PlayerKey));
	
	GoToPlayer = MakeShared<FAivState>(
		[this](AAIController* AIController) {
			AIController->MoveToActor(PlayerPawn, 100.0f);
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FAivState> {
			EPathFollowingStatus::Type State = AIController->GetMoveStatus();


			if (State == EPathFollowingStatus::Moving)
			{
				return nullptr;
			}

			AActor* BestBall = Cast<AActor>(BlackboardComponent->GetValueAsObject(BestBallKey));

			if (!BestBall->IsAttachedTo(AIController->GetPawn())) 
			{
				return SearchForBall;
			}

			if (BestBall)
			{
				EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(PlayerPawn, 100.0f);
				if (MoveResult == EPathFollowingRequestResult::AlreadyAtGoal)
				{
					BestBall->AttachToActor(AIController->GetWorld()->GetFirstPlayerController()->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform);
					BestBall->SetActorRelativeLocation(FVector(0, 0, 0));
					BestBall = nullptr;					
				}
				else
				{
					return nullptr;
				}
			}
			return SearchForBall;
		}
	);

	SearchForBall = MakeShared<FAivState>(
		[this](AAIController* AIController) {

			AGameModeBase* GameMode = AIController->GetWorld()->GetAuthGameMode();
			ATagGameGameMode* AIGameMode = Cast<ATagGameGameMode>(GameMode);
			const TArray<ABall*>& BallsList = AIGameMode->GetBalls();

			ABall* NearestBall = nullptr;

			for (int32 i = 0; i < BallsList.Num(); i++)
			{
				if (!BallsList[i]->GetAttachParentActor() &&
					(!NearestBall ||
						FVector::Distance(AIController->GetPawn()->GetActorLocation(), BallsList[i]->GetActorLocation()) <
						FVector::Distance(AIController->GetPawn()->GetActorLocation(), NearestBall->GetActorLocation())))
				{
					NearestBall = BallsList[i];
				}
			}

			BlackboardComponent->SetValueAsObject(BestBallKey, NearestBall);
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FAivState> {
			AActor* BestBall = Cast<AActor>(BlackboardComponent->GetValueAsObject(BestBallKey));
			if (BestBall)
			{
				return GoToBall;
			}
			else {
				return Stop;
			}
		}
	);

	GoToBall = MakeShared<FAivState>(
		[this](AAIController* AIController) {

			AActor* BestBall = Cast<AActor>(BlackboardComponent->GetValueAsObject(BestBallKey));
			AIController->MoveToActor(BestBall, 100.0f);
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FAivState> {
			EPathFollowingStatus::Type State = AIController->GetMoveStatus();

			AActor* BestBall = Cast<AActor>(BlackboardComponent->GetValueAsObject(BestBallKey));

			if (State == EPathFollowingStatus::Moving)
			{
				if (BestBall->GetAttachParentActor())
				{
					return Stop;
				}
				return nullptr;
			}
			return GrabBall;
		}
	);

	GrabBall = MakeShared<FAivState>(
		[this](AAIController* AIController)
		{

			AActor* BestBall = Cast<AActor>(BlackboardComponent->GetValueAsObject(BestBallKey));
			if (BestBall->GetAttachParentActor())
			{
				BestBall = nullptr;
			}
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FAivState> {


			AActor* BestBall = Cast<AActor>(BlackboardComponent->GetValueAsObject(BestBallKey));
			if (!BestBall)
			{
				return SearchForBall;
			}

			BestBall->AttachToActor(AIController->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform);
			BestBall->SetActorRelativeLocation(FVector(0, 0, 0));

			return GoToPlayer;
		}
	);

	Stop = MakeShared<FAivState>(
		[this](AAIController* AIController)
		{
			AIController->StopMovement();
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FAivState> {

			return SearchForBall;
		}
	);

	CurrentState = SearchForBall;
	CurrentState->CallEnter(this);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState)
	{
		CurrentState = CurrentState->CallTick(this, DeltaTime);
	}
	else
	{
		CurrentState = SearchForBall;
		CurrentState->CallEnter(this);
	}
}

