#pragma once

#include "Behaviours/Behaviour.h"
class GOAP_Move : public Behaviour
{
public:
	GOAP_Move(ACPP_Agent* pOwner, GOAP_Action* a_ActionToGoTo);
	~GOAP_Move() {};

	void Update();
	Behaviour* CheckConditions();

private:

	AActor* m_pTargetActor;//Stores the actor that we are chasing

	GOAP_Action* m_pCurrentAction;//The action we are moving to
};
