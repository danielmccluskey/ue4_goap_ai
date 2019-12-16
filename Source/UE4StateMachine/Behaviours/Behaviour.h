#pragma once

#include "AIAgents/CPP_Agent.h"
#include "AIAgents/GOAP_Agent.h"
/// <summary>
/// Class for behaviours to inherit from for the Finite State Machine
/// </summary>
class Behaviour
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Behaviour"/> class.
	/// </summary>
	/// <param name="pOwner">The agent.</param>
	Behaviour(ACPP_Agent* pOwner) { m_pOwner = pOwner; }
	/// <summary>
	/// Finalizes an instance of the <see cref="Behaviour"/> class.
	/// </summary>
	virtual ~Behaviour() {};
	/// <summary>
	/// Updates this instance.
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// Checks the conditions.
	/// </summary>
	/// <returns></returns>
	virtual Behaviour* CheckConditions() = 0;
	/// <summary>
	/// Gets the owner.
	/// </summary>
	/// <returns></returns>
	ACPP_Agent* GetOwner() { return m_pOwner; }

private:
	/// <summary>
	/// Stores a reference to the owner
	/// </summary>
	ACPP_Agent* m_pOwner;
};