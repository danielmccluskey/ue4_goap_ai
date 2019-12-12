#pragma once
#include "Behaviours/Behaviour.h"

class ACPP_Agent;
class GOAP_Planner;
class GOAP_Action;

class GOAP_PerformAction : public Behaviour
{
public:
	GOAP_PerformAction(ACPP_Agent* pOwner, GOAP_Action* a_pAction);
	~GOAP_PerformAction() {};

	void Update();
	Behaviour* CheckConditions();

private:

	GOAP_Action* m_pAction;
};
