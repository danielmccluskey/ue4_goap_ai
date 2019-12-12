#include "GOAP/Systems/GOAP_Action.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
GOAP_Action::GOAP_Action()
{
	m_smPreconditions = TSet<TPair<FString, bool>>();
	m_smEffects = TSet<TPair<FString, bool>>();
}

GOAP_Action::~GOAP_Action()
{
}

void GOAP_Action::ResetAction()
{
	m_bInRange = false;
	m_paTarget = nullptr;
	ResetGA();
}

void GOAP_Action::ResetGA()
{
}

bool GOAP_Action::IsActionFinished()
{
	return false;
}

bool GOAP_Action::CheckPreCondition(AActor* a_paAIAgent)
{
	return false;
}

bool GOAP_Action::PerformAction(AActor* a_paAIAgent)
{
	return false;
}

bool GOAP_Action::NeedsToBeInRange()
{
	return false;
}

bool GOAP_Action::IsAgentInRange()
{
	return m_bInRange;
}

void GOAP_Action::SetInRange(bool a_bTrue)
{
	m_bInRange = a_bTrue;
}

void GOAP_Action::AddPreCondition(FString a_sPreCondition, bool a_bValue)
{
	m_smPreconditions.Add(TPair<FString, bool>(a_sPreCondition, a_bValue));
}

void GOAP_Action::RemovePreCondition(FString a_sPreCondition)
{
	TPair<FString, bool> pPreConToRemove = TPair<FString, bool>();
	for (TPair<FString, bool> pPreCon : m_smPreconditions)
	{
		if (pPreCon.Key == a_sPreCondition)
		{
			pPreConToRemove = pPreCon;
			m_smPreconditions.Remove(pPreConToRemove);
		}
	}
}

void GOAP_Action::AddEffect(FString a_sEffect, bool a_bValue)
{
	m_smEffects.Add(TPair<FString, bool>(a_sEffect, a_bValue));
}

void GOAP_Action::RemoveEffect(FString a_sEffect)
{
	TPair<FString, bool> pEffectToRemove = TPair<FString, bool>();
	for (TPair<FString, bool> pEffect : m_smEffects)
	{
		if (pEffect.Key == a_sEffect)
		{
			pEffectToRemove = pEffect;
			m_smEffects.Remove(pEffectToRemove);
		}
	}
}

TSet<TPair<FString, bool>> GOAP_Action::GetPreConditions()
{
	return m_smPreconditions;
}

TSet<TPair<FString, bool>> GOAP_Action::GetEffects()
{
	return m_smEffects;
}