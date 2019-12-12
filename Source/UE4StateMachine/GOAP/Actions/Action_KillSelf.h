#pragma once
#include "GOAP/Systems/GOAP_Action.h"
class Action_KillSelf :
	public GOAP_Action
{
public:
	Action_KillSelf();
	~Action_KillSelf();

	virtual void ResetGA() override;
	virtual bool IsActionFinished() override;
	virtual bool CheckPreCondition(AActor* a_paAIAgent) override;
	virtual bool PerformAction(AActor* a_paAIAgent) override;
	virtual bool NeedsToBeInRange() override;

private:
	bool m_bRequiresInRange = true;
	bool m_bPerformingAction = false;
};
