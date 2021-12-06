#include <iostream>
#include <map>
#include <vector>
#include "GraphGenerator.cpp"

using namespace std;

class GraphOperator {

	public:

		map<int, bool> visitedDFS;
		map<int, bool> visitedBFS;
		
		vector<vector<int>>  vectorBFS; 
		int bfsVectorCounter = 0;

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
			
			//Find the connected component of the root argument vertice
			findConnectedComponents(start, graph, root);
			
			//Go through entire AVL tree to find all connected components
			Node * leftNode = root->leftChild;
			Node * rightNode = root->rightChild;
			if(leftNode != null)
				connectedComponents(leftNode->number, graph, leftNode);
			if(rightNode != null)
				connectedComponents(rightNode->number, graph, rightNode);

		}

		void findConnectedComponents(int start, GraphGenerator graph, Node * root){
			//create a list of connected vertices
			vector<int> queueAdj;
			
			//if the starting vertice is already visited, no use in continuing as its connected component already found
			if(!visitedBFS.find(start))
                        {
				//Found a new component, increment the 2d vector
				bfsVectorCounter++;

				//If starting vertice not visited, mark it as visited and push 
                                visitedBFS[start] = true;
				vectorBFS[bfsVectorCounter].push_back(start);	

                                llNode * curr = graph.getAdjList(start);
				queueAdj.push_back(start);

				while(!queueAdj.empty)
				{
					curr = graph.getAdjList(queueAdj.pop_back)();
                                	while(curr->next)
                                	{
                                        	if(!visitedBFS.find(curr->next->number))
                                        	{
                                                	queueAdj.push_back(curr->next->number);
                                                	visitedBFS[curr->next->number] = true;
							vectorBFS[bfsVectorCounter].push_back(curr->next->number);
                                        	}
                                	}
				}
                        }


		}

}
