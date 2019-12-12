#pragma once

#include "AIAgents/CPP_Agent.h"
#include "AIAgents/GOAP_Agent.h"
class Behaviour
{
public:
	Behaviour(ACPP_Agent* pOwner) { m_pOwner = pOwner; }
	virtual ~Behaviour() {};

	virtual void Update() = 0;
	virtual Behaviour* CheckConditions() = 0;

	ACPP_Agent* GetOwner() { return m_pOwner; }

private:
	ACPP_Agent* m_pOwner;
};