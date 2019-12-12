// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP_Agent.h"
#include "GOAP/Systems/GOAP_Action.h"
#include "CPP_Agent.h"
#include "AIController.h"
#include "Behaviours/GOAP_Idle.h"

#include "GOAP/Actions/Action_BiteActor.h"
#include "GOAP/Actions/Action_KillSelf.h"
#include "GOAP/Actions/Action_Mutate.h"
#include "GOAP/Actions/Action_Wander.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

AGOAP_Agent::AGOAP_Agent()
{
	LoadAvailableActions();
}

void AGOAP_Agent::LoadAvailableActions()
{
	//Add all of the actions that the actor can use to a list.
	m_sAvailableActions.Add(new Action_KillSelf);
	m_sAvailableActions.Add(new Action_BiteActor);
	m_sAvailableActions.Add(new Action_Mutate);
	m_sAvailableActions.Add(new Action_Wander);
}

TSet<TPair<FString, bool>> AGOAP_Agent::GetPlayersCurrentState()
{
	//Create a list of Player states that tell the GOAP planner what actions it can perform
	//Used to compare against an actions pre conditions.
	TSet<TPair<FString, bool>> PlayerStateData = TSet<TPair<FString, bool>>();
	PlayerStateData.Add(TPair<FString, bool>("Infected", GetInfectedStatus()));
	PlayerStateData.Add(TPair<FString, bool>("BittenActor", HasBittenSomeone()));
	PlayerStateData.Add(TPair<FString, bool>("Mutated", GetMutatedStatus()));
	return PlayerStateData;
}

TSet<TPair<FString, bool>> AGOAP_Agent::CreateGoalState()
{
	//Create a goal state specific to Infected and Non infected actors.
	//You can have multiple goals.
	TSet<TPair<FString, bool>> GoalData = TSet<TPair<FString, bool>>();

	if (GetInfectedStatus() == true)
	{
		GoalData.Add(TPair<FString, bool>("Mutated", true));//If they are infected, their goal is to Mutate and change colour
		GoalData.Add(TPair<FString, bool>("KillSelf", true));//If they are infected, their goal is to Kill themself after biting another agent.
	}
	else
	{
		GoalData.Add(TPair<FString, bool>("Wander", true));//If they are uninfected, just wander.
	}
	return GoalData;
}

void AGOAP_Agent::PlanFailed(TSet<TPair<FString, bool>> a_kvpFailedGoal)
{
}

void AGOAP_Agent::PlanFound(TSet<TPair<FString, bool>> a_kvpGoal, TQueue<GOAP_Action*> a_qActionQueue)
{
}

void AGOAP_Agent::AllActionsFinished()
{
}

void AGOAP_Agent::AbortPlan(GOAP_Action * a_FailedAction)
{
}

bool AGOAP_Agent::MoveAgentToAction(GOAP_Action * a_NextAction)
{
	if (a_NextAction != nullptr)//Null check
	{
		AAIController* pAIController = Cast<AAIController>(GetController());
		if (pAIController)
		{
			float fDistance = FVector::Dist(GetActorLocation(), a_NextAction->m_paTarget->GetActorLocation());//Get distance between Actor and target

			UAIBlueprintHelperLibrary::SimpleMoveToActor(pAIController, a_NextAction->m_paTarget);//Move to target actor

			if (fDistance <= m_fArrivalDistance)//If we are close enough
			{
				return true;//We have arrived
			}
		}
	}
	return false;
}

bool AGOAP_Agent::MoveAgentToAction(GOAP_Action * a_NextAction, bool a_bVector)
{
	if (a_NextAction != nullptr)
	{
		AAIController* pAIController = Cast<AAIController>(GetController());
		if (pAIController)
		{
			float fDistance = FVector::Dist(GetActorLocation(), a_NextAction->m_vTargetLocation);//Get distance between actor and target.

			UAIBlueprintHelperLibrary::SimpleMoveToLocation(pAIController, a_NextAction->m_vTargetLocation);//Move there
			if (fDistance <= m_fArrivalDistance)//Have we arrived?
			{
				return true;
			}
		}
	}
	return false;
}

TSet<GOAP_Action*> AGOAP_Agent::GetActionList()
{
	return m_sAvailableActions;
}

bool AGOAP_Agent::HasBittenSomeone()
{
	return m_bHasBittenSomeone;
}

void AGOAP_Agent::SetHasBittenSomeone(bool a_bBitten)
{
	m_bHasBittenSomeone = true;
}

bool AGOAP_Agent::GetInfectedStatus()
{
	return m_bInfected;
}

void AGOAP_Agent::SetInfectedStatus(bool a_bTrue)
{
	m_bInfected = a_bTrue;
}

bool AGOAP_Agent::GetMutatedStatus()
{
	return m_bHasMutated;
}

void AGOAP_Agent::SetMutatedStatus(bool a_bTrue)
{
	m_bHasMutated = a_bTrue;
}