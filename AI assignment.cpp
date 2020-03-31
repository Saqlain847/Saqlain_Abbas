#include<iostream>
#include<string>
#include<set>
#include<queue>
#include<typeinfo>
#include<stack>
using namespace std;
string states[8] = { "(AgentInRoom1, Room1Dusty, Roam2Dusty)",
	"(AgentInRoom1, Room1Dusty, Roam2Clean)",
	"(AgentInRoom1, Room1Clean, Roam2Dusty)",
	"(AgentInRoom1, Room1Clean, Roam2Clean)",
	"(AgentInRoom2, Room1Dusty, Roam2Dusty)",
	"(AgentInRoom2, Room1Dusty, Roam2Clean)",
	"(AgentInRoom2, Room1Clean, Roam2Dusty)",
	"(AgentInRoom2, Room1Clean, Roam2Clean)" };
string actions[3] = { "Clean","MoveToRoom1","MoveToRoom2" };
int transitionModel[8][3];

class Node {
public:
	Node* parent;
	int state;
	int action;
	int pathCost;

	Node(Node* parent = nullptr, int state = -1, int action = -1, int pathCost = 0)
	{
		this->parent = parent;
		this->state = state;
		this->action = action;
		this->pathCost = pathCost;
	}
	void display()
	{
		cout << "Parent : " << parent << endl;
		cout << "State : " << state << endl;
		cout << "Action : " << action << endl;
		cout << "Cost : " << pathCost<< endl;
		cout << "************************\n";
	}
	bool goalTest(int a)
	{
		if (this->state == a)
		{
			return true;
		}
		return false;
	}
	/*bool operator< (const Node& other) const {
		return cost < other.pathCost;
	}*/
};
queue<Node>frontier;
set<int>exploredSet;
bool exp(set<Node*>& explored, Node* node)
{
	bool find = false;
	set <Node*> ::iterator itr;

	for (itr = explored.begin(); itr != explored.end(); ++itr)
	{
		if ((*itr)->state == node->state)
		{
			find = true;
			break;
		}
	}
	return find;
}
bool front(int a)
{
	return true;
}
Node search(string startState, string finalState)
{
	bool array[8];
	for (int i = 0; i < 8; i++)
	{
		array[i] = false;
	}
	int goal = 0;
	Node n;
	for (int i = 0; i < 8; i++)
	{
		if (startState == states[i])
		{
			n.state = i;
			n.action = -1;
			n.pathCost = 0;
			n.parent = NULL;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (finalState == states[i])
		{
			goal = i;
		}
	}
	if (n.goalTest(goal))
	{
		return n;
	}
	else
	{
		frontier.push(n);
		array[n.state] = true;
	}
	Node child;
	do {
		exploredSet.insert(frontier.front().action);
		frontier.pop();
		for (int i = 0; i < 3; i++)
		{

			child.state = transitionModel[n.state][i];
			child.pathCost = n.pathCost + 1;
			child.pathCost = n.pathCost + 1;
			child.action = i;
			child.parent = &n;
			if (child.goalTest(goal))
			{
				return child;
			}
			else
			{
				if (!array[child.state])
				{
					frontier.push(child);
					array[child.state] = true;
				}
			}
		}
		n = frontier.front();
	} while (!frontier.empty());

}
void display(string startState, string finalState)
{
	Node result;
	result = search(startState, finalState);
	if (result.action == -1)
	{
		cout << "Robot is already in its Position\n";
	}
	else
	{
		set<int>::iterator it;
		for (auto it = exploredSet.begin(); it != exploredSet.end(); it++)
		{
			if ((*it == 0))
				cout << "Clean ->";
			if (*it == 1)
				cout << "Move to Room 1 ->";
			if (*it == 0)
				cout << "Move to Room 2 ->";
		}
		if (result.action == 0)
			cout << "Clean";
		if (result.action == 1)
			cout << "Move to Room 1";
		if (result.action == 2)
			cout << "Move to Room 2";
	}
	cout << endl;
}
class Data
{
public:
	int m, n, t;
	string* states, * actions;
	string startState;
	string endState;
	int** taransitionTable;
};

void input(Data& input)
{
	cin >> input.m >> input.n >> input.t;

	input.states = new string[input.m];
	input.actions = new string[input.n];
	input.taransitionTable = new int* [input.m];

	for (int i = 0; i < input.m; i++)
		input.taransitionTable[i] = new int[input.n];

	getchar();

	for (int i = 0; i < input.m; i++)
	{
		if (i == 0)
			cin.ignore();
		getline(cin, input.states[i]);
	}

	getchar();

	for (int i = 0; i < input.n; i++)
		getline(cin, input.actions[i]);

	getchar();

	for (int i = 0; i < input.m; i++)
		cin >> input.taransitionTable[i][0] >> input.taransitionTable[i][1] >> input.taransitionTable[i][2];

	getchar();
	getchar();
}
int main()
{

//	freopen("input.txt", "r", stdin);

	string startAndEndState;
	Data data;
	input(data);



	cout << "States\n";
	for (int i = 0; i < 8; i++)
	{
		cout << states[i] << endl;
	}
	string initialState;
	string goalState;
	cout << "Enter Initial state : ";
	getline(cin, initialState);
	cout << "Enter goal state : ";
	getline(cin, goalState);
	display(initialState, goalState);
	/*Node result;
	result = search(initailState, goalState);
	if (result.action == -1)
	{
		cout << "Robot is already in its Position\n";
	}
	result.display();*/
	
	system("pause");
	
	return 0;
}