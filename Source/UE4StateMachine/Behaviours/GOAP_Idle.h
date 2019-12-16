#pragma once
#include "Behaviours/Behaviour.h"

class ACPP_Agent;
class GOAP_Planner;

/// <summary>
/// The behaviour that creates the plan of actions for the agent
/// </summary>
/// <seealso cref="Behaviour" />
class GOAP_Idle : public Behaviour
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GOAP_Idle"/> class.
	/// </summary>
	/// <param name="pOwner">The agent.</param>
	GOAP_Idle(ACPP_Agent* pOwner);
	/// <summary>
	/// Finalizes an instance of the <see cref="GOAP_Idle"/> class.
	/// </summary>
	~GOAP_Idle();
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void Update();
	/// <summary>
	/// Checks the conditions.
	/// </summary>
	/// <returns></returns>
	Behaviour* CheckConditions();

private:
	/// <summary>
	/// Stores the actor that we are chasing
	/// </summary>
	AActor* m_pTargetActor;
	/// <summary>
	/// Stores the queue of actions.
	/// </summary>
	TQueue<GOAP_Action*> ActionPlan;
	/// <summary>
	/// Planner reference
	/// </summary>
	GOAP_Planner* m_ActionPlanner;
};
