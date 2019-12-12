#include "GOAP/Systems/Node.h"
#include "GOAP/Systems/GOAP_Action.h"

Node::Node(Node* a_nParentNode, float a_fCost, TSet<TPair<FString, bool>> a_smState, GOAP_Action* a_Action)
{
	m_nParentNode = a_nParentNode;
	m_fCost = a_fCost;
	m_smState = a_smState;
	m_Action = a_Action;
}

Node::~Node()
{
}