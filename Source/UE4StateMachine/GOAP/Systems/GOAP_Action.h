#pragma once

#include "Set.h"
#include "Map.h"
#include "String"
#include "CoreMinimal.h"

class AActor;

/// <summary>
/// Class to inherit for all GOAP actions.
/// </summary>
class GOAP_Action
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GOAP_Action"/> class.
	/// </summary>
	GOAP_Action();
	/// <summary>
	/// Finalizes an instance of the <see cref="GOAP_Action"/> class.
	/// </summary>
	~GOAP_Action();

	/// <summary>
	/// The figurative cost of running this action
	/// </summary>
	float m_fCost = 1.0f;
	/// <summary>
	/// The target actor that this action is targeting
	/// </summary>
	AActor* m_paTarget;
	/// <summary>
	/// Used if target is a location rather than an actor.
	/// </summary>
	FVector m_vTargetLocation;
	/// <summary>
	/// Name of the action, used for debugging
	/// </summary>
	FString m_sActionName;

	/// <summary>
	/// Resets everything for this action.
	/// </summary>
	void ResetAction();
	/// <summary>
	/// Resets the actions variables such as range
	/// </summary>
	virtual void ResetGA();
	/// <summary>
	/// Determines whether the action is finished.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the action is finished; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsActionFinished();
	/// <summary>
	/// Checks the procedural precondition.
	/// </summary>
	/// <param name="a_paAIAgent">The agent performing the action.</param>
	/// <returns></returns>
	virtual bool FindTarget(AActor* a_paAIAgent);
	/// <summary>
	/// Performs the action.
	/// </summary>
	/// <param name="a_paAIAgent">The agent performing the action.</param>
	/// <returns></returns>
	virtual bool PerformAction(AActor* a_paAIAgent);
	/// <summary>
	/// Checks if the agent needs to to be in range of the target to perform this action.
	/// </summary>
	/// <returns></returns>
	virtual bool NeedsToBeInRange();

	/// <summary>
	/// Determines whether [agent is in range].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [agent is in range]; otherwise, <c>false</c>.
	/// </returns>
	bool IsAgentInRange();
	/// <summary>
	/// Sets the in range variable.
	/// </summary>
	/// <param name="a_bTrue">if set to <c>true</c> [a b true].</param>
	void SetInRange(bool a_bTrue);
	/// <summary>
	/// Adds a pre condition to this action.
	/// </summary>
	/// <param name="a_sPreCondition">Precondition string.</param>
	/// <param name="a_bValue">Requirement of precondition</param>
	void AddPreCondition(FString a_sPreCondition, bool a_bValue);
	/// <summary>
	/// Removes a certain pre condition.
	/// </summary>
	/// <param name="a_sPreCondition">Precondition string.</param>
	void RemovePreCondition(FString a_sPreCondition);
	/// <summary>
	/// Adds an effect to this action.
	/// </summary>
	/// <param name="a_sEffect">Effect string to add.</param>
	/// <param name="a_bValue">Effect value</param>
	void AddEffect(FString a_sEffect, bool a_bValue);
	/// <summary>
	/// Removes the effect.
	/// </summary>
	/// <param name="a_sEffect">Effect string to remove</param>
	void RemoveEffect(FString a_sEffect);

	/// <summary>
	/// Gets the pre conditions for this action.
	/// </summary>
	/// <returns>Preconditions for this action</returns>
	TSet<TPair<FString, bool>> GetPreConditions();
	/// <summary>
	/// Gets the effects for this action.
	/// </summary>
	/// <returns>Effects for this action</returns>
	TSet<TPair<FString, bool>> GetEffects();

private:
	/// <summary>
	/// The preconditions this effect has
	/// </summary>
	TSet<TPair<FString, bool>> m_smPreconditions;

	/// <summary>
	/// The effects that performing this action causes.
	/// </summary>
	TSet<TPair<FString, bool>> m_smEffects;

	/// <summary>
	/// Is the agent in range?
	/// </summary>
	bool m_bInRange = false;
};
