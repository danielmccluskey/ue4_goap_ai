#pragma once
#include "GOAP/Systems/GOAP_Action.h"
class Action_BiteActor :
	public GOAP_Action
{
public:
	Action_BiteActor();
	~Action_BiteActor();

	virtual void ResetGA() override;
	virtual bool IsActionFinished() override;
	virtual bool CheckPreCondition(AActor* a_paAIAgent) override;
	virtual bool PerformAction(AActor* a_paAIAgent) override;
	virtual bool NeedsToBeInRange() override;

private:
	bool m_bRequiresInRange = true;
	bool m_bPerformingAction = false;
};
