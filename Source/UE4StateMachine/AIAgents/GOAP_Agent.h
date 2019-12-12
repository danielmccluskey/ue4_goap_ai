// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIAgents/CPP_Agent.h"
#include "GOAP_Agent.generated.h"

/**
 *
 */
UCLASS()
class UE4STATEMACHINE_API AGOAP_Agent : public ACPP_Agent
{
	GENERATED_BODY()
public:
	AGOAP_Agent();
	/// <summary>
	/// Loads the available actions and puts them into m_sAvailableActions.
	/// </summary>
	void LoadAvailableActions();

	/// <summary>
	/// Gets the current state of the player.
	/// </summary>
	/// <returns></returns>
	TSet<TPair<FString, bool>> GetPlayersCurrentState();

	/// <summary>
	/// Creates the players Goal state
	/// </summary>
	/// <returns></returns>
	TSet<TPair<FString, bool>> CreateGoalState();

	/// <summary>
	/// Handles a plan failing
	/// </summary>
	/// <param name="a_kvpFailedGoal">The goal we failed to achieve</param>
	void PlanFailed(TSet<TPair<FString, bool>> a_kvpFailedGoal);

	/// <summary>
	/// Function to handle finding a successful plan
	/// </summary>
	/// <param name="a_kvpGoal">The goal that it satisfied</param>
	/// <param name="a_qActionQueue">The action plan</param>
	void PlanFound(TSet<TPair<FString, bool>> a_kvpGoal, TQueue<GOAP_Action*> a_qActionQueue);

	/// <summary>
	/// Function to be called when all actions in the action queue have been performed
	/// </summary>
	void AllActionsFinished();

	/// <summary>
	/// Function for handling when an action fails to perform
	/// </summary>
	/// <param name="a_FailedAction">The action that failed.</param>
	void AbortPlan(GOAP_Action* a_FailedAction);

	/// <summary>
	///	Target Actor version
	/// Moves the agent to the actions location
	/// </summary>
	/// <param name="a_NextAction">Action to move to</param>
	/// <returns></returns>
	bool MoveAgentToAction(GOAP_Action* a_NextAction);

	/// <summary>
	///	FVector Location version
	/// Moves the agent to the actions location.
	/// </summary>
	/// <param name="a_NextAction">Action to move to</param>
	/// <param name="a_bVector">Unused, just used for function overload, just set to false.</param>
	/// <returns></returns>
	bool MoveAgentToAction(GOAP_Action* a_NextAction, bool a_bVector);

	/// <summary>
	/// Grabs the list of actions this actor can perform
	/// </summary>
	/// <returns></returns>
	TSet<GOAP_Action*> GetActionList();

	//Self explanatory Get and set functions\/

	bool HasBittenSomeone();
	void SetHasBittenSomeone(bool a_bBitten);
	bool GetInfectedStatus();
	void SetInfectedStatus(bool a_bTrue);
	bool GetMutatedStatus();
	void SetMutatedStatus(bool a_bTrue);

	int m_iHealth;
	float m_fArrivalDistance = 100.0f;

private:
	UPROPERTY(EditAnywhere)
		bool m_bInfected = false;//Tells us whether the agent is infected or not

	bool m_bHasBittenSomeone = false;
	bool m_bHasMutated = false;

	TSet<GOAP_Action*> m_sAvailableActions;
};
