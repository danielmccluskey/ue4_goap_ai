#include "GOAP/Actions/Action_Wander.h"
#include "AIAgents/CPP_Agent.h"
#include "AIAgents/GOAP_Agent.h"
#include "AIController.h"

#include "NavigationSystem.h"
#include "AbstractNavData.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

Action_Wander::Action_Wander()
{
	//How this action will affect the Players state
	AddEffect("Wander", true);

	m_sActionName = "Wander";
	m_fCost = 1.0f;//Figurative cost of performing this action.
	m_bRequiresInRange = true;
}

Action_Wander::~Action_Wander()
{
}

void Action_Wander::ResetGA()
{
	m_bPerformingAction = false;
	m_paTarget = nullptr;
	m_vTargetLocation = FVector::ZeroVector;
}

bool Action_Wander::IsActionFinished()
{
	return m_bPerformingAction;
}

bool Action_Wander::FindTarget(AActor* a_paAIAgent)
{
	AGOAP_Agent* pAIAgent = Cast<AGOAP_Agent>(a_paAIAgent);
	if (pAIAgent)
	{
		AAIController* pAIController = Cast<AAIController>(pAIAgent->GetController());

		if (pAIController)//Null check
		{
			UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(pAIAgent->GetWorld());//Get the current Navmesh system data
			m_vTargetLocation = NavSys->GetRandomReachablePointInRadius(pAIAgent->GetWorld(), pAIController->GetNavAgentLocation(), 20000.0f);//Choose a random location on the navmesh
			if (m_vTargetLocation != FVector::ZeroVector)//Has found a random location
			{
				return true;
			}
		}
	}

	return false;
}

bool Action_Wander::PerformAction(AActor* a_paAIAgent)
{
	m_bPerformingAction = true;
	return true;
}

bool Action_Wander::NeedsToBeInRange()
{
	return m_bRequiresInRange;
}