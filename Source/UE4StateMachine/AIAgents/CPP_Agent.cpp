// Fill out your copyright notice in the Description page of Project Settings.

#include "AIAgents/CPP_Agent.h"
#include "Behaviours/Behaviour.h"
#include "Behaviours/GOAP_Idle.h"

#include "GOAP/Systems/GOAP_Planner.h"
#include "GOAP/Systems/GOAP_Action.h"

// Sets default values
ACPP_Agent::ACPP_Agent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_Agent::BeginPlay()
{
	Super::BeginPlay();

	m_pIdleState = new GOAP_Idle(this);
	m_pCurrentBehaviour = m_pIdleState;
}

// Called every frame
void ACPP_Agent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pCurrentBehaviour)
	{
		Behaviour* pNewBehaviour = m_pCurrentBehaviour->CheckConditions();
		if (pNewBehaviour)
		{
			delete m_pCurrentBehaviour;

			m_pCurrentBehaviour = pNewBehaviour;
		}
		else if (m_bInterruptBehaviour)
		{
			m_bInterruptBehaviour = false;
			delete m_pCurrentBehaviour;
			m_pCurrentBehaviour = new GOAP_Idle(this);
		}

		m_pCurrentBehaviour->Update();
	}
}

void ACPP_Agent::InterruptBehaviour()
{
	m_bInterruptBehaviour = true;
}

// Called to bind functionality to input
void ACPP_Agent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}