#pragma once
#include <functional>
#include "../utility/PriorityQueue.h"
#include "DecisionAlgorithm.h"

using namespace std;

template <class Domain, class Node, class TopLevelAction>
class ScalarBackup : public DecisionAlgorithm<Domain, Node, TopLevelAction>
{
	typedef typename Domain::State State;
	typedef typename Domain::Cost Cost;

public:
	ScalarBackup(string sorting)
		: sortingFunction(sorting)
	{}

	Node* backup(PriorityQueue<Node*>& open, vector<TopLevelAction>& tlas, Node* start)
	{
		// First things first, reorder open so it matches our expansion policy needs
		sortOpen(open);

		Node* goalPrime = open.top();

		// Only move one step towards best on open
		while (goalPrime->getParent() != start)
			goalPrime = goalPrime->getParent();

		goalPrime->markStart();

		return goalPrime;
	}

private:
	void sortOpen(PriorityQueue<Node*>& open)
	{
		if (sortingFunction == "minimin")
			open.swapComparator(Node::compareNodesF);
		else if (sortingFunction == "bellman")
			open.swapComparator(Node::compareNodesFHat);
<<<<<<< HEAD
		else if (sortingFunction == "ie")
			open.swapComparator(Node::compareNodesLC);
		else if (sortingFunction == "iep")
			open.swapComparator(Node::compareNodesUC);
=======
>>>>>>> cpu
	}

protected:
	string sortingFunction;
};