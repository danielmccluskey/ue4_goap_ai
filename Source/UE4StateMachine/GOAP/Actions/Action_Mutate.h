#pragma once
#include "GOAP/Systems/GOAP_Action.h"

class UMaterialInstanceDynamic;

class Action_Mutate :
	public GOAP_Action
{
public:
	Action_Mutate();
	~Action_Mutate();

	virtual void ResetGA() override;
	virtual bool IsActionFinished() override;
	virtual bool CheckPreCondition(AActor* a_paAIAgent) override;
	virtual bool PerformAction(AActor* a_paAIAgent) override;
	virtual bool NeedsToBeInRange() override;

	void CreateDynamicMaterial(AActor * pOwner);

private:
	bool m_bRequiresInRange = true;
	bool m_bPerformingAction = false;

	UMaterialInstanceDynamic* m_pDynamicMaterial;
};
