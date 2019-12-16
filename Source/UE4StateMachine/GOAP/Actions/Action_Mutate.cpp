#include "GOAP/Actions/Action_Mutate.h"
#include "AIAgents/CPP_Agent.h"
#include "AIAgents/GOAP_Agent.h"
#include "AIController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

Action_Mutate::Action_Mutate()
{
	//Players State preconditions for this action
	AddPreCondition("Infected", true);
	AddPreCondition("Mutated", false);

	//How this action will affect the Players state
	AddEffect("Mutated", true);

	m_sActionName = "Mutate";
	m_fCost = 1.0f;//Figurative cost of performing this action.
	m_bRequiresInRange = false;
}

Action_Mutate::~Action_Mutate()
{
}

void Action_Mutate::ResetGA()
{
	m_bPerformingAction = false;
	m_paTarget = nullptr;
}

bool Action_Mutate::IsActionFinished()
{
	return m_bPerformingAction;
}

bool Action_Mutate::FindTarget(AActor* a_paAIAgent)
{
	return true;//This Action does not have any other requirements other than the State preconditions, so we can just return true.
}

bool Action_Mutate::PerformAction(AActor* a_paAIAgent)
{
	CreateDynamicMaterial(a_paAIAgent);//Create the material, should really pass this through on creation.
	m_pDynamicMaterial->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0.0f));//Set the material colour
	AGOAP_Agent* pAgent = Cast<AGOAP_Agent>(a_paAIAgent);
	if (pAgent)
	{
		pAgent->SetMutatedStatus(true);//Player has mutated
	}
	m_bPerformingAction = true;
	return true;
}

bool Action_Mutate::NeedsToBeInRange()
{
	return m_bRequiresInRange;
}

void Action_Mutate::CreateDynamicMaterial(AActor* pOwner)
{
	if (pOwner)
	{
		USkeletalMeshComponent* pMesh = Cast<AGOAP_Agent>(pOwner)->GetMesh();
		if (pMesh)
		{
			UMaterialInterface* pMaterial = pMesh->GetMaterial(0);
			if (pMaterial)
			{
				m_pDynamicMaterial = UMaterialInstanceDynamic::Create(pMaterial, pOwner);
				pMesh->SetMaterial(0, m_pDynamicMaterial);
			}
		}
	}
}