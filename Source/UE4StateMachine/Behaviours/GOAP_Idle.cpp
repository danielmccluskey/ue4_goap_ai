#include "Behaviours/GOAP_Idle.h"
#include "Behaviours/GOAP_Move.h"
#include "AIAgents/GOAP_Agent.h"
#include "GOAP/Systems/GOAP_Planner.h"
#include "AIAgents/CPP_Agent.h"
#include "AIController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

GOAP_Idle::GOAP_Idle(ACPP_Agent* pOwner) : Behaviour(pOwner)
{
	m_ActionPlanner = new GOAP_Planner();//Create a new planner

	TSet<TPair<FString, bool>> WorldState = Cast<AGOAP_Agent>(pOwner)->GetPlayersCurrentState();//Get the players current state (Infected, mutated, hasbitten etc.)
	TSet<TPair<FString, bool>> GoalState = Cast<AGOAP_Agent>(pOwner)->CreateGoalState();//Get the players current goals.

	TSet<GOAP_Action*> sActionList = Cast<AGOAP_Agent>(pOwner)->GetActionList();//Get the players available actions

	m_ActionPlanner->CreateActionPlan(pOwner, sActionList, WorldState, GoalState, &ActionPlan);//Create an actionplan (Outputs to ActionPlan)
}

GOAP_Idle::~GOAP_Idle()
{
	if (m_ActionPlanner)
	{
		delete m_ActionPlanner;
	}
}

void GOAP_Idle::Update()
{
}

Behaviour* GOAP_Idle::CheckConditions()
{
	if (!ActionPlan.IsEmpty())//If there actually is a plan.
	{
		GOAP_Action* pOutAction;
		ActionPlan.Peek(pOutAction);//Get the first action from the plan
		return new GOAP_Move(GetOwner(), pOutAction);//Start moving to the action
	}
	return new GOAP_Idle(GetOwner());//There is no plan so we need to replan.

	//TO DO - Set replan to a timer so its not running every single frame.
}