#ifndef GRAPHO
#define GRAPHO

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

			cout << "Checking: " << start << endl;
			
			visitedDFS[start] = true;
			
			cout << "After true init" << endl;
			
			llNode * curr = graph.getAdjList(start);
			
			cout << "After adjList" << endl;
			if(curr == NULL)
				cout << "YEP" << endl;
			cout << curr->number << endl;
			cout <<"asdasd" << endl;	
			while(curr->next) {
				cout << "Checking for " << start << endl;
				if(visitedDFS.find(curr->next->number)->second) return true;
				if(!visitedDFS.find(curr->next->number)->second) return isAcyclic(curr->next->number, graph);
			}

		}
	
		
		// function that uses BFS to print all connected components
		void connectedComponents(int start, GraphGenerator graph, Node * root) {
			cout << "IN CONNECTED" << endl;
			//Find the connected component of the root argument vertice
			findConnectedComponents(start, graph, root);
			
			//Go through entire AVL tree to find all connected components
			Node * leftNode = root->leftChild;
			Node * rightNode = root->rightChild;
			if(leftNode != NULL)
				connectedComponents(leftNode->number, graph, leftNode);
			if(rightNode != NULL)
				connectedComponents(rightNode->number, graph, rightNode);

		}

		

		void findConnectedComponents(int start, GraphGenerator graph, Node * root){
			cout << "IN FIND" << endl;
			//create a list of connected vertices
			vector<int> queueAdj;
			int vectorBack;
			//if the starting vertice is already visited, no use in continuing as its connected component already found
			std::map<int, bool>::iterator it = visitedBFS.find(start);
			if(it != visitedBFS.end() && !it->second)
                        {
				//Found a new component, increment the 2d vector
				bfsVectorCounter++;

				//If starting vertice not visited, mark it as visited and push the vertice onto vector 
                                visitedBFS[start] = true;
				vectorBFS[bfsVectorCounter].push_back(start);	

				//let the current vertice be pushed onto queueAdj
                                llNode * curr;
				queueAdj.push_back(start);

				//only stop looking when no more connected vertices left
				while(!queueAdj.empty())
				{
					//let the current vertice be grabbed from queueAdj
					vectorBack = queueAdj.back();
					curr = graph.getAdjList(vectorBack);
					queueAdj.pop_back();

					//only stop looking at adjacent vertices of the current vertice when there are no more
                                	while(curr->next && curr != NULL)
                                	{
						std::map<int, bool>::iterator it = visitedDFS.find(curr->next->number);
						
						//If a node hasn't been visited already, push it onto the queue, mark it visited, push it onto the vector
                                        	if(it != visitedBFS.end() && !it->second)
                                        	{
                                                	queueAdj.push_back(curr->next->number);
                                                	visitedBFS[curr->next->number] = true;
							vectorBFS[bfsVectorCounter].push_back(curr->next->number);
                                        	}
                                	}
				}

				//Sort and print out the vector
				//sort(vectorBFS[bfsVectorCounter].begin(), vectorBFS[bfsVectorCounter].end());
				for(int i = 0; i < vectorBFS[bfsVectorCounter].size(); i++)
				{
					cout << vectorBFS[bfsVectorCounter][i];
					if(i < vectorBFS[bfsVectorCounter].size()-1)
					{
						cout << " ";
					}
				}
				cout << endl;
                        }


		}

};

#endif
