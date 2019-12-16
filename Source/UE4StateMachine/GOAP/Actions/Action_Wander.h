#pragma once
#include "GOAP/Systems/GOAP_Action.h"
/// <summary>
/// The action that uninfected agents use to roam the map randomly
/// </summary>
/// <seealso cref="GOAP_Action" />
class Action_Wander :
	public GOAP_Action
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Action_Wander"/> class.
	/// </summary>
	Action_Wander();
	/// <summary>
	/// Finalizes an instance of the <see cref="Action_Wander"/> class.
	/// </summary>
	~Action_Wander();

	virtual void ResetGA() override;
	virtual bool IsActionFinished() override;
	virtual bool FindTarget(AActor* a_paAIAgent) override;
	virtual bool PerformAction(AActor* a_paAIAgent) override;
	virtual bool NeedsToBeInRange() override;

	void CreateDynamicMaterial(AActor* pOwner);

private:
	/// <summary>
	/// Whether this action requires the agent to be in range or not
	/// </summary>
	bool m_bRequiresInRange = true;
	/// <summary>
	/// Has the agent performed the action yet?
	/// </summary>
	bool m_bPerformingAction = false;
};
