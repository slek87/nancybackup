#pragma once
#include <unordered_map>
#include <functional>
#include "../utility/PriorityQueue.h"
#include"../utility/ResultContainer.h"


using namespace std;

template <class Domain>
class OfflineAStar {
public:
    typedef typename Domain::State State;
	typedef typename Domain::Cost Cost;
    typedef typename Domain::HashState Hash;

    struct Node	{
		Cost g;
		Cost h;
		Cost d;
		Cost derr;
		Cost epsH;
		Cost epsD;
		Node* parent;
		State stateRep;
		int owningTLA;
		bool open;
		int delayCntr;
		// DiscreteDistribution distribution;

	public:
		Cost getGValue() const { return g; }
		Cost getHValue() const { return h; }
		Cost getDValue() const { return d; }
		Cost getFValue() const { return g + h; }
		State getState() const { return stateRep; }
		Node* getParent() const { return parent; }

		void setHValue(Cost val) { h = val; }
		void setGValue(Cost val) { g = val; }
		void setDValue(Cost val) { d = val; }
		void setState(State s) { stateRep = s; }
		void setParent(Node* p) { parent = p; }

		bool onOpen() { return open; }
		void close() { open = false; }
		void reOpen() { open = true; }

		void incDelayCntr() { delayCntr++; }
		int getDelayCntr() { return delayCntr; }

		void markStart() { stateRep.markStart(); }

		Node(Cost g, Cost h, Cost d, State state, Node* parent)
			: g(g), h(h), d(d), stateRep(state), parent(parent){
			open = true;
			delayCntr = 0;
		}

		friend std::ostream& operator<<(std::ostream& stream, const Node& node) {
			stream << node.getState() << endl;
			stream << "f: " << node.getFValue() << endl;
			stream << "g: " << node.getGValue() << endl;
			stream << "h: " << node.getHValue() << endl;
			stream << "d: " << node.getDValue() << endl;
			stream << "action generated by: " << node.getState().getLabel() << endl;
			stream << "-----------------------------------------------" << endl;
			stream << endl;
			return stream;
		}

		static bool compareNodesF(const Node* n1, const Node* n2)
		{
			// Tie break on g-value
			if (n1->getFValue() == n2->getFValue())
			{
				return n1->getGValue() > n2->getGValue();
			}
			return n1->getFValue() < n2->getFValue();
		}

		static bool compareNodesH(const Node* n1, const Node* n2)
		{
			if (n1->getHValue() == n2->getHValue())
			{
				return n1->getGValue() > n2->getGValue();
			}
			return n1->getHValue() < n2->getHValue();
		}
	};

    OfflineAStar(Domain& domain) : domain(domain) {}

    ResultContainer solve(){
        ResultContainer res;
        PriorityQueue<Node*> open;
        unordered_map<State, Node*, Hash> closed;

        Node* start = new Node(0, domain.heuristic(domain.getStartState()), domain.distance(domain.getStartState()),
			domain.getStartState(), NULL);
        open.swapComparator(Node::compareNodesF);
        open.push(start);

		start_state = start->getState().toString();

        while (!open.empty()){
			Node* cur = open.top();

            if (domain.isGoal(cur->getState()))
			{
				res.solutionFound = true;
				res.solutionCost = cur->getFValue();
				goal_node = cur;
				goal_state = cur->getState().toString();

                return res;
			}

			res.nodesExpanded++;

			open.pop();
			cur->close();
			vector<State> children = domain.successors(cur->getState());
			res.nodesGenerated += children.size();

			for (State child : children){
				Node* childNode = new Node(cur->getGValue() + domain.getEdgeCost(child),
					domain.heuristic(child), domain.distance(child), child, cur);
				bool dup = duplicateDetection(childNode, closed, open);

				// Duplicate detection
				if (!dup)
				{
					open.push(childNode);
					closed[child] = childNode;
				}
				else
					delete childNode;
			}
        }
		
		cout << "No goal was found" << endl;
		return res;
    }

	void printPlan(){
		if (goal_node){
			if (domain.getDomainName() == "PancakePuzzle" || domain.getDomainName() == "PancakePuzzleDPS"){
				vector <int> plan;
				cout << "*Tracing from goal to starting starting:" << endl;
				while (goal_node->parent){
					plan.push_back(goal_node->getState().getLabel());
					cout << goal_node->getState() << endl;
					goal_node = goal_node->parent;
				}
				cout << goal_node->getState() << endl;
				cout << "*End trace. Printing plan:" << endl;

				cout << "# " << start_state;
				for (int i = plan.size() - 1; i >= 0; --i){
					cout << plan[i] << endl;
				}
				cout << "# " << goal_state;
				cout << endl;

			} else {

				vector <char> plan;
				cout << "*Tracing from goal to starting starting:" << endl;
				while (goal_node->parent){
					plan.push_back(goal_node->getState().getLabel());
					cout << goal_node->getState() << endl;
					goal_node = goal_node->parent;
				}
				cout << goal_node->getState() << endl;
				cout << "*End trace. Printing plan:" << endl;

				cout << "# " << start_state;
				for (int i = plan.size() - 1; i >= 0; --i){
					cout << plan[i] << endl;
				}
				cout << "# " << goal_state;
				cout << endl;

			}

		} else {
			cout << "No Goal." << endl;
		}
	}

private:
	static bool duplicateDetection(Node* node, unordered_map<State, Node*, Hash>& closed, PriorityQueue<Node*>& open)
	{
		// Check if this state exists 
		typename unordered_map<State, Node*, Hash>::iterator it = closed.find(node->getState());

		if (it != closed.end())
		{
			// This state has been generated before, check if its node is on OPEN
			if (it->second->onOpen())
			{
				// This node is on OPEN, keep the better g-value
				if (node->getGValue() < it->second->getGValue())
				{
					it->second->setGValue(node->getGValue());
					it->second->setParent(node->getParent());
					it->second->setHValue(node->getHValue());
					it->second->setDValue(node->getDValue());
					it->second->setState(node->getState());
				}
			}
			else
			{
				// This node is on CLOSED, compare the f-values. If this new f-value is better, reset g, h, and d. 
				// Then reopen the node.
				if (node->getFValue() < it->second->getFValue())
				{
					it->second->setGValue(node->getGValue());
					it->second->setParent(node->getParent());
					it->second->setHValue(node->getHValue());
					it->second->setDValue(node->getDValue());
					it->second->setState(node->getState());
					it->second->reOpen();
					open.push(it->second);
				}
			}

			return true;
		}

		return false;
	}


protected:
	Domain & domain;
	string start_state;
	string goal_state;
	Node* goal_node;
};