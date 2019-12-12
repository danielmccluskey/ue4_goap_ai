#pragma once
#include "Containers/Queue.h"
#include "Containers/Map.h"
#include "Containers/Set.h"
#include "List.h"
#include "CoreMinimal.h"

class Node;
class AActor;
class GOAP_Action;

class GOAP_Planner
{
public:
	GOAP_Planner();
	~GOAP_Planner();
	TQueue<GOAP_Action*>* m_qActionQueue;
	TQueue<GOAP_Action*> m_qQueue;

	/// <summary>
	/// Begins the sequence to create a plan of Actions.
	/// Actions are returned in a_qActionPlan.
	/// </summary>
	/// <param name="a_pAIAgent">Reference to the Actor to make the plan for.</param>
	/// <param name="a_sAvailableActions">List of Actions that are available to that actor.</param>
	/// <param name="a_smWorldState">The current states of that actor.</param>
	/// <param name="a_smGoalState">That Actors goals.</param>
	/// <param name="a_qActionPlan">Out variable, will contain the final plan.</param>
	void CreateActionPlan(AActor* a_pAIAgent, TSet<GOAP_Action*> a_sAvailableActions, TSet<TPair<FString, bool>>& a_smWorldState, TSet<TPair<FString, bool>>& a_smGoalState, TQueue<GOAP_Action*>* a_qActionPlan);

private:

	/// <summary>
	/// Builds the list of Actions to use
	/// Returns a list of nodes to a_nNodeList which contain path of actions that satisfy a goal.
	/// </summary>
	/// <param name="a_nParent">The Beginning node</param>
	/// <param name="a_nNodeList">An empty List of nodes to Output to</param>
	/// <param name="a_sUsableActions">A List of the actions the Actor can currently run</param>
	/// <param name="a_smGoalState">The Actors goals</param>
	/// <returns></returns>
	bool BuildGOAPPlan(Node* a_nParent, TArray<Node*>& a_nNodeList, TSet<GOAP_Action*> a_sUsableActions, TSet<TPair<FString, bool>> a_smGoalState);

	/// <summary>
	/// Checks if any of the Players Goals can be satisfied in the given state.
	/// Used for checking if an action will satisfy a players goal.
	/// </summary>
	/// <param name="a_smGoal">The goals that need satisfying</param>
	/// <param name="a_smState">The players current state.</param>
	/// <returns></returns>
	bool GoalMatchesState(TSet<TPair<FString, bool>> a_smGoal, TSet<TPair<FString, bool>> a_smState);

	/// <summary>
	/// Checks if the preconditions of an action match the players state.
	/// Used for determining whether a player can actually run an action.
	/// </summary>
	/// <param name="a_smPreConditions">An actions preconditions.</param>
	/// <param name="a_smState">The Players current state.</param>
	/// <returns></returns>
	bool MatchesPlayersCurrentState(TSet<TPair<FString, bool>> a_smPreConditions, TSet<TPair<FString, bool>> a_smState);

	/// <summary>
	/// Makes a list of Actions, excluding the given action.
	/// </summary>
	/// <param name="a_sActions">Actions that that the actor can currently use.</param>
	/// <param name="a_ExcludedAction">The action that they just performed</param>
	/// <returns></returns>
	TSet<GOAP_Action*> GatherNewActions(TSet<GOAP_Action*> a_sActions, GOAP_Action* a_ExcludedAction);

	/// <summary>
	/// Refreshes the state of the actor.
	/// After an action is chosen, running this function will update the simulated player state and apply the effects of the performed action.
	/// </summary>
	/// <param name="a_smCurrentState">The players current state.</param>
	/// <param name="a_smStateChange">The effects of the action that was just performed.</param>
	/// <returns></returns>
	TSet<TPair<FString, bool>> RefreshPlayersState(TSet<TPair<FString, bool>> a_smCurrentState, TSet<TPair<FString, bool>> a_smStateChange);
};
