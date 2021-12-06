#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "GraphOperator.cpp"

using namespace std;

int main(int argc, char *argv[]) {
	GraphGenerator graphs(argv[1]
	cout << "The in order traversal:" << endl;
	graphs.inOrder();
	cout << "The pre order traversal:" << endl;
	graphs.preOrder();
	cout << "Is acyclic(Yes/No):" << endl;
	if(isAcyclic(graphs))
	{
		cout << "Yes" << endl;
	}	
	else
	{
		cout << "No" << endl;
	}
	cout << "Connected Components:" << endl;
	Node * node1 = graphs.avlTreeRoot;
	connectedComponents(node1->number, graphs, node1);
}
