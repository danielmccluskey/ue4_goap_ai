#pragma once
#include "Containers/Queue.h"
#include "Containers/Map.h"
#include "Containers/Set.h"

class GOAP_Action;

/// <summary>
/// Node class for storing actions and the states that they satisfy.
/// </summary>
class Node
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Node"/> class.
	/// </summary>
	Node();
	/// <summary>
	/// Initializes a new instance of the <see cref="Node"/> class.
	/// </summary>
	/// <param name="a_nParentNode">The parent node.</param>
	/// <param name="a_fCost">The cost of this node.</param>
	/// <param name="a_smState">The states that this action satisfies</param>
	/// <param name="a_Action">The action this node performs</param>
	Node(Node* a_nParentNode, float a_fCost, TSet<TPair<FString, bool>> a_smState, GOAP_Action* a_Action);
	/// <summary>
	/// Finalizes an instance of the <see cref="Node"/> class.
	/// </summary>
	~Node();

	/// <summary>
	/// Stores the parent (The preceeding node)
	/// </summary>
	Node* m_nParentNode = nullptr;
	/// <summary>
	/// The cost of this action and its preceeding nodes.
	/// </summary>
	float m_fCost = 1.0f;
	/// <summary>
	/// The states that this action satisfies
	/// </summary>
	TSet<TPair<FString, bool>> m_smState = TSet<TPair<FString, bool>>();
	/// <summary>
	/// The action this node completes
	/// </summary>
	GOAP_Action* m_Action = nullptr;
};
