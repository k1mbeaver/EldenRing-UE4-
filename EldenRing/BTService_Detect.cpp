// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "MonsterController.h"
#include "MonsterCharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
    NodeName = TEXT("Detect");
    Interval = 0.3f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
        return;

    UWorld* World = ControllingPawn->GetWorld();
    FVector Center = ControllingPawn->GetActorLocation();
    float DetectRadius = 1000.0f;

    if (nullptr == World)
        return;

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
    bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(OverlapResult.GetActor());
            //AMyAICharacter* MyAICharacter = Cast<AMyAICharacter>(OverlapResult.GetActor());

             //  && MyCharacter->GetController()->IsPlayerController()
            if (MyCharacter)
            {
                int SkillTime = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AMonsterController::SkillTime);
                SkillTime++;

                if (SkillTime > 20) // 스킬 쿨이 50이 넘어가면 사용후
                {
                    SkillTime = 0; // 초기화
                }

                OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMonsterController::SkillTime, SkillTime);
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterController::TargetKey, MyCharacter);
                DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

                DrawDebugPoint(World, MyCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
                DrawDebugLine(World, ControllingPawn->GetActorLocation(), MyCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
                return;
            }

            else
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterController::TargetKey, nullptr);
            }
        }
    }
    DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}

