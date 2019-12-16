#include "GOAP/Actions/Action_KillSelf.h"
#include "AIAgents/CPP_Agent.h"
#include "AIAgents/GOAP_Agent.h"
#include "AIController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

Action_KillSelf::Action_KillSelf()
{
	//Players State preconditions for this action
	AddPreCondition("BittenActor", true);

	//How this action will affect the Players state
	AddEffect("KillSelf", true);

	m_sActionName = "Kill self";
	m_fCost = 1.0f;//Figurative cost of performing this action.
	m_bRequiresInRange = false;
}

Action_KillSelf::~Action_KillSelf()
{
}

void Action_KillSelf::ResetGA()
{
	m_bPerformingAction = false;
	m_paTarget = nullptr;
}

bool Action_KillSelf::IsActionFinished()
{
	return m_bPerformingAction;
}

bool Action_KillSelf::FindTarget(AActor* a_paAIAgent)
{
	return true;//This Action does not have any other requirements other than the State preconditions, so we can just return true.
}

bool Action_KillSelf::PerformAction(AActor* a_paAIAgent)
{
	a_paAIAgent->Destroy();//Destroy me
	m_bPerformingAction = true;
	return true;
}

bool Action_KillSelf::NeedsToBeInRange()
{
	return m_bRequiresInRange;
}