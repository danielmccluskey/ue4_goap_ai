#include "GOAP/Actions/Action_BiteActor.h"
#include "AIAgents/CPP_Agent.h"
#include "AIAgents/GOAP_Agent.h"
#include "AIController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
Action_BiteActor::Action_BiteActor()
{
	//Players State preconditions for this action
	AddPreCondition("Infected", true);

	//How this action will affect the Players state
	AddEffect("BittenActor", true);

	m_sActionName = "Bite a person";
	m_fCost = 1.0f;//Figurative cost of performing this action.
	m_bRequiresInRange = true;
}

Action_BiteActor::~Action_BiteActor()
{
}

void Action_BiteActor::ResetGA()
{
	m_bPerformingAction = false;
	m_paTarget = nullptr;
}

bool Action_BiteActor::IsActionFinished()
{
	return m_bPerformingAction;
}

bool Action_BiteActor::CheckPreCondition(AActor * a_paAIAgent)
{
	TArray<AActor*> aFoundAgents;//To store list of all agents
	UGameplayStatics::GetAllActorsOfClass(a_paAIAgent->GetWorld(), AGOAP_Agent::StaticClass(), aFoundAgents);//Get All agents

	float fClosestDistance = 100000.0f;//Max distance to compare to
	m_paTarget = nullptr;//Reset target actor

	for (AActor* a_Actor : aFoundAgents)//Loop through actor list
	{
		if (a_Actor)//Null check
		{
			if (a_Actor != a_paAIAgent && Cast<AGOAP_Agent>(a_Actor)->GetInfectedStatus() == false)//Check current loop actor is not self and not already infected
			{
				float fThisDistance = FVector::Dist(a_paAIAgent->GetActorLocation(), a_Actor->GetActorLocation());//Get distance between two actors
				if (fThisDistance <= 0.0f)//If the target is me, temp fix for broken check above.
				{
					continue;
				}
				if (fThisDistance <= fClosestDistance)//If closer than last actor
				{
					m_paTarget = a_Actor;//Set new target
					fClosestDistance = fThisDistance;//New closest distance
				}
			}
		}
	}

	if (m_paTarget == nullptr)//If we have not found a target
	{
		return false;//We cannot perform the action
	}

	return true;//We have found a target so we can perform the action.
}

bool Action_BiteActor::PerformAction(AActor * a_paAIAgent)
{
	AGOAP_Agent* pTargetAgent = Cast<AGOAP_Agent>(m_paTarget);
	if (pTargetAgent)//Null check
	{
		pTargetAgent->SetInfectedStatus(true);//Infect them
		pTargetAgent->InterruptBehaviour();//Interrupt their Wander behaviour so they replan and start infecting others.
	}
	AGOAP_Agent* pAgent = Cast<AGOAP_Agent>(a_paAIAgent);
	if (pAgent)
	{
		pAgent->SetHasBittenSomeone(true);//We have bitten someone, time to die
		pAgent->InterruptBehaviour();//Interrupt so we can die.
	}

	m_bPerformingAction = true;
	return true;
}

bool Action_BiteActor::NeedsToBeInRange()
{
	return m_bRequiresInRange;
}