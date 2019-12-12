#pragma once

#include "Set.h"
#include "Map.h"
#include "String"
#include "CoreMinimal.h"

class AActor;

class GOAP_Action
{
public:
	GOAP_Action();
	~GOAP_Action();

	float m_fCost = 1.0f;
	AActor* m_paTarget;
	FVector m_vTargetLocation;//Used if target is a location rather than an actor.
	FString m_sActionName;

	void ResetAction();
	virtual void ResetGA();
	virtual bool IsActionFinished();
	virtual bool CheckPreCondition(AActor* a_paAIAgent);
	virtual bool PerformAction(AActor* a_paAIAgent);
	virtual bool NeedsToBeInRange();

	bool IsAgentInRange();
	void SetInRange(bool a_bTrue);
	void AddPreCondition(FString a_sPreCondition, bool a_bValue);
	void RemovePreCondition(FString a_sPreCondition);
	void AddEffect(FString a_sEffect, bool a_bValue);
	void RemoveEffect(FString a_sEffect);

	TSet<TPair<FString, bool>> GetPreConditions();
	TSet<TPair<FString, bool>> GetEffects();

private:

	TSet<TPair<FString, bool>> m_smPreconditions;
	TSet<TPair<FString, bool>> m_smEffects;

	bool m_bInRange = false;
};
