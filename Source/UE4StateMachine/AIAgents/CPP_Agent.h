// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Containers/Queue.h"
#include "CPP_Agent.generated.h" // IMPORTANT - This has to go at the end of the includes!!!

// Forward declarations
class Behaviour;
class GOAP_Action;

UCLASS()
class UE4STATEMACHINE_API ACPP_Agent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Agent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InterruptBehaviour();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetBehaviour(Behaviour* a_pBehaviour) { m_pCurrentBehaviour = a_pBehaviour; }

private:
	Behaviour* m_pCurrentBehaviour;
	Behaviour* m_pIdleState;
	bool m_bInterruptBehaviour = false;
};
