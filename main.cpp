#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "GraphOperator.cpp"
#include "GraphGenerator.cpp"
using namespace std;

int main(int argc, char *argv[]) {
	GraphGenerator graphs(argv[1]);
	Node * rootNode = graphs.avlTreeRoot;
	cout << "The in order traversal:" << endl;
	graphs.inOrder(rootNode);
	cout << endl;
	cout << "The pre order traversal:" << endl;
	graphs.preOrder(rootNode);
	cout << endl;
	/*
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
	connectedComponents(node1->number, graphs, node1); */
}
