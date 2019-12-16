#pragma once
#include "GOAP/Systems/GOAP_Action.h"
/// <summary>
/// Action for biting another actor in the scene
/// </summary>
/// <seealso cref="GOAP_Action" />
class Action_BiteActor :
	public GOAP_Action
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Action_BiteActor"/> class.
	/// </summary>
	Action_BiteActor();
	/// <summary>
	/// Finalizes an instance of the <see cref="Action_BiteActor"/> class.
	/// </summary>
	~Action_BiteActor();

	virtual void ResetGA() override;
	virtual bool IsActionFinished() override;
	virtual bool FindTarget(AActor* a_paAIAgent) override;
	virtual bool PerformAction(AActor* a_paAIAgent) override;
	virtual bool NeedsToBeInRange() override;

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
