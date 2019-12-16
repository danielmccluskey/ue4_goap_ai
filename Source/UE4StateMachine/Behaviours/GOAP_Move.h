#pragma once

#include "Behaviours/Behaviour.h"
/// <summary>
/// The behaviour that moves the AI agents to their target for their action
/// </summary>
/// <seealso cref="Behaviour" />
class GOAP_Move : public Behaviour
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GOAP_Move"/> class.
	/// </summary>
	/// <param name="pOwner">The agent performing the action.</param>
	/// <param name="a_ActionToGoTo">The action to move to</param>
	GOAP_Move(ACPP_Agent* pOwner, GOAP_Action* a_ActionToGoTo);
	/// <summary>
	/// Finalizes an instance of the <see cref="GOAP_Move"/> class.
	/// </summary>
	~GOAP_Move() {};

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
	/// The action we are moving to
	/// </summary>
	GOAP_Action* m_pCurrentAction;
};
