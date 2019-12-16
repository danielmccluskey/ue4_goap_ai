#pragma once
#include "GOAP/Systems/GOAP_Action.h"

class UMaterialInstanceDynamic;
/// <summary>
/// The action agents use when they have just been bitten
/// </summary>
/// <seealso cref="GOAP_Action" />
class Action_Mutate :
	public GOAP_Action
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Action_Mutate"/> class.
	/// </summary>
	Action_Mutate();
	/// <summary>
	/// Finalizes an instance of the <see cref="Action_Mutate"/> class.
	/// </summary>
	~Action_Mutate();

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

	/// <summary>
	/// The material colour for changing colour
	/// </summary>
	UMaterialInstanceDynamic* m_pDynamicMaterial;
};
