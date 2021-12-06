#include <iostream>
#include <map>
#include <vector>
#include "GraphGenerator.cpp"

using namespace std;

class GraphOperator {

	public:

		map<int, bool> visitedDFS;
		map<int, bool> visitedBFS;
		bool visitedAllBFS;
		vector<int>  vectorBFS; 

		// function that uses DFS to check for cycles
		bool isAcyclic(int start, GraphGenerator graph) {

			visitedDFS[start] = true;

			bool allVisited = true;
			llNode * curr = graph.getAdjList(start);
			
			while(curr->next) {
				if(visited.find(curr->next->number)) return true;
				if(!visited.find(curr->next->number)) return isAcyclic(curr->next->number, graph);

			}

		}

		// function that uses BFS to print all connected components
		void connectedComponents(int start, GraphGenerator graph, Node * root) {
			
			if(!visitedBFS.find(start))
			{
				visitedBFS[start] = true;
				llNode * curr = graph.getAdjList(start);

				while(curr->next)
				{	
					if(!visitedBFS.find(curr->next->number))
					{
						vectorBFS.push_back(curr->next->number);
						visitedBFS[curr->next->number] = true;
					}
				}

			}

			Node * leftNode = root->leftChild;
			Node * rightNode = root->rightChild;
			if(leftNode != null)
				connectedComponents(leftNode->number, graph, leftNode);
			if(rightNode != null)
				connectedComponents(rightNode->number, graph, rightNode);

		}

}
