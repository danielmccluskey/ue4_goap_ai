#pragma once
#include "Behaviours/Behaviour.h"

class ACPP_Agent;
class GOAP_Planner;

class GOAP_Idle : public Behaviour
{
public:
	GOAP_Idle(ACPP_Agent* pOwner);
	~GOAP_Idle();

	void Update();
	Behaviour* CheckConditions();

private:

	AActor* m_pTargetActor;//Stores the actor that we are chasing
	TQueue<GOAP_Action*> ActionPlan;//Stores the queue of actions.

	GOAP_Planner* m_ActionPlanner;//Planner reference
};
