#pragma once
#include "Behaviours/Behaviour.h"

class ACPP_Agent;
class GOAP_Planner;
class GOAP_Action;

/// <summary>
/// The behaviour that performs the given action
/// </summary>
/// <seealso cref="Behaviour" />
class GOAP_PerformAction : public Behaviour
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GOAP_PerformAction"/> class.
	/// </summary>
	/// <param name="pOwner">The Agent performing the action.</param>
	/// <param name="a_pAction">The action to perform.</param>
	GOAP_PerformAction(ACPP_Agent* pOwner, GOAP_Action* a_pAction);
	~GOAP_PerformAction() {};

	/// <summary>
	/// Updates this instance.
	/// </summary>
	void Update();
	/// <summary>
	/// Checks the conditions of this behaviour for the exit route.
	/// </summary>
	/// <returns></returns>
	Behaviour* CheckConditions();

private:
	/// <summary>
	/// Stores the action to perform
	/// </summary>
	GOAP_Action* m_pAction;
};
