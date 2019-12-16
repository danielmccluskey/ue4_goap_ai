#include "GOAP/Systems/GOAP_Planner.h"
#include "GOAP/Systems/GOAP_Action.h"
#include "GOAP/Systems/Node.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Algo/Reverse.h"

GOAP_Planner::GOAP_Planner()
{
}

GOAP_Planner::~GOAP_Planner()
{
}

void GOAP_Planner::CreateActionPlan(AActor* a_pAIAgent, TSet<GOAP_Action*> a_sAvailableActions, TSet<TPair<FString, bool>>& a_smWorldState, TSet<TPair<FString, bool>>& a_smGoalState, TQueue<GOAP_Action*>* a_qActionPlan)
{
	//Reset all of the Action specific variables
	for (GOAP_Action* pAction : a_sAvailableActions)
	{
		pAction->ResetAction();
	}

	//Find the actions that this agent is currently able to perform
	TSet<GOAP_Action*> sUsableActions;
	for (GOAP_Action* pAction : a_sAvailableActions)
	{
		if (pAction->FindTarget(a_pAIAgent))//If the agent can actually run that action.
		{
			sUsableActions.Add(pAction);
		}
	}

	//Create a Tree diagram of every path we are able to take, then ride it to the goal.
	TArray<Node*> nLeaves;
	Node* nStartNode = new Node(nullptr, 0, a_smWorldState, nullptr);//Beginning node, for other nodes to parent to.
	bool bSuccessfulTree = BuildGOAPPlan(nStartNode, nLeaves, sUsableActions, a_smGoalState);

	if (!bSuccessfulTree)
	{
		return;//Could not build a successful plan, no combination of actions found that satisfy a goal.
	}

	//Find the cheapest path from the Tree diagram.
	Node* nCheapestPlan = nullptr;
	for (Node* nNode : nLeaves)
	{
		if (nCheapestPlan == nullptr)//If cheapest plan has not yet been set.
		{
			nCheapestPlan = nNode;
		}
		else
		{
			if (nNode->m_fCost < nCheapestPlan->m_fCost)//If the cost of the current plan is cheaper than the chosen plan
			{
				nCheapestPlan = nNode;//Replace it with the cheaper one
			}
		}
	}

	//Create the final plan of actions
	TSet<GOAP_Action*> lFinishedPlan = TSet<GOAP_Action*>();
	while (nCheapestPlan)//While the cheapest plan does not equal the beginning parent node.
	{
		if (nCheapestPlan->m_Action)//Null check
		{
			lFinishedPlan.Add(nCheapestPlan->m_Action);//Add it to the plan
		}
		if (nCheapestPlan->m_nParentNode == nullptr)//Null check
		{
			nCheapestPlan = nullptr;//End the while loop
		}
		else
		{
			nCheapestPlan = nCheapestPlan->m_nParentNode;//Move on to the parent node.
		}
	}
	TArray<GOAP_Action*> lFinishedPlanB = lFinishedPlan.Array();//Convert the Set to a TArray.

	Algo::Reverse(lFinishedPlanB);//Reverse the TArray so that the first action the actor needs to perform is at the beginning of the list.

	a_qActionPlan->Empty();//Empty the ActionQueue

	//Convert the TArray to a Queue to run through
	for (GOAP_Action* pAction : lFinishedPlanB)
	{
		a_qActionPlan->Enqueue(pAction);//Queue the new action.
	}

	return;
}

bool GOAP_Planner::BuildGOAPPlan(Node* a_nParent, TArray<Node*>& a_nNodeList, TSet<GOAP_Action*> a_sUsableActions, TSet<TPair<FString, bool>> a_smGoalState)
{
	bool bFoundSuccessfulPath = false;
	for (GOAP_Action* pAction : a_sUsableActions)//Loop through all of the actions that we can actually currently perform
	{
		if (MatchesPlayersCurrentState(pAction->GetPreConditions(), a_nParent->m_smState))//Check that the current action can actually be performed by the actor, by comparing the preconditions of the action to the players current state.
		{
			TSet<TPair<FString, bool>> smCurrentState = RefreshPlayersState(a_nParent->m_smState, pAction->GetEffects());//Create a new state, formed from the players state, but updated with the Effects of the action we just checked.
			Node* nNewNode = new Node(a_nParent, (a_nParent->m_fCost + pAction->m_fCost), smCurrentState, pAction);//Create a new node with the newly calculated values.

			if (GoalMatchesState(a_smGoalState, smCurrentState))//Check if any of the goals can be satisfied by the new updated state.
			{
				a_nNodeList.Add(nNewNode);//Add the new node to the Node list.
				bFoundSuccessfulPath = true;//We have a path that satisfies a goal!

				//Don't break out yet, since other actions may satisfy other goals.
			}
			else
			{
				//Recursive part, check the rest of the actions with the newly calculated player state.

				TSet<GOAP_Action*> sChildBranches = GatherNewActions(a_sUsableActions, pAction);//Gather a list of actions, excluding the one we just used.
				bool bFoundSecondPath = BuildGOAPPlan(nNewNode, a_nNodeList, sChildBranches, a_smGoalState);
				if (bFoundSecondPath)
				{
					bFoundSuccessfulPath = true;//We found another way to satisfy a goal.
				}
			}
		}
	}
	return bFoundSuccessfulPath;
}

bool GOAP_Planner::GoalMatchesState(TSet<TPair<FString, bool>> a_smGoal, TSet<TPair<FString, bool>> a_smState)
{
	bool bIsInState = false;
	for (TPair<FString, bool> mGoal : a_smGoal)//Loop through the given goals
	{
		for (TPair<FString, bool> mState : a_smState)//Loop through the given states
		{
			if (mGoal.Key == mState.Key)//If the keys are the same
			{
				if (mGoal.Value == mState.Value)//If the values of the keys are also the same
				{
					bIsInState = true;
					break;
				}
			}
		}
	}
	return bIsInState;
}

bool GOAP_Planner::MatchesPlayersCurrentState(TSet<TPair<FString, bool>> a_smPreConditions, TSet<TPair<FString, bool>> a_smState)
{
	bool bAllPreconditionsMet = true;
	bool bPreConditionMet = false;
	for (TPair<FString, bool> mPreCons : a_smPreConditions)
	{
		for (TPair<FString, bool> mState : a_smState)
		{
			if (mPreCons.Key == mState.Key)
			{
				if (mPreCons.Value == mState.Value)
				{
					bPreConditionMet = true;
				}
			}
		}
		if (bPreConditionMet == false)//If ONE or more of the preconditions isn't met it means we cannot run this action.
		{
			bAllPreconditionsMet = false;
		}
	}
	return bAllPreconditionsMet;
}

TSet<GOAP_Action*> GOAP_Planner::GatherNewActions(TSet<GOAP_Action*> a_sActions, GOAP_Action* a_ExcludedAction)
{
	TSet<GOAP_Action*> sBranches = TSet<GOAP_Action*>();
	for (GOAP_Action* pAction : a_sActions)
	{
		if (pAction != a_ExcludedAction)
		{
			sBranches.Add(pAction);
		}
	}
	return sBranches;
}

TSet<TPair<FString, bool>> GOAP_Planner::RefreshPlayersState(TSet<TPair<FString, bool>> a_smCurrentState, TSet<TPair<FString, bool>> a_smStateChange)
{
	TSet<TPair<FString, bool>> smNewState = TSet<TPair<FString, bool>>();//Stores the new state

	TPair<FString, bool> mPairToRemove;//The State that we need to remove from the given state

	//Copy the given state to the new state.
	for (TPair<FString, bool > mState : a_smCurrentState)
	{
		smNewState.Add(TPair<FString, bool>(mState.Key, mState.Value));
	}

	for (TPair<FString, bool> mChange : a_smStateChange)
	{
		bool bKeyExists = false;

		for (TPair<FString, bool> mState : smNewState)
		{
			if (mChange.Key == mState.Key)//If this key exists in the old states.
			{
				bKeyExists = true;
				mPairToRemove = mState;
				break;
			}
		}

		if (bKeyExists)
		{
			smNewState.Remove(mPairToRemove);//Remove is from the old state
			TPair<FString, bool> mUpdatedPair = TPair<FString, bool>(mChange.Key, mChange.Value);
			smNewState.Add(mUpdatedPair);//Add the updated state to the new state list
		}
		else
		{
			smNewState.Add(TPair<FString, bool>(mChange.Key, mChange.Value));//Otherwise we can just add it again.
		}
	}
	return smNewState;
}