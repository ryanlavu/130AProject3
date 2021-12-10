#ifndef GRAPHO
#define GRAPHO

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "GraphGenerator.cpp"

using namespace std;


class GraphOperator {
	public:

		map<int, bool> visitedDFS;
		map<int, bool> visitedBFS;
       		bool isCyclic = false;
		vector<vector<int>>  vectorBFS; 
		int bfsVectorCounter = 0;

		// function that uses DFS to check for cycles
	    	void isAcyclicChk(Node *node, GraphGenerator graph, bool *result){
            		if(node == NULL || *result) return;

            		*result = isAcyclic(node->number, node->number, graph);
            		if(*result || isCyclic) return;

            		isAcyclicChk(node->leftChild, graph, result);
            		if (*result|| isCyclic) return;

            		isAcyclicChk(node->rightChild, graph, result);

		}

				
	    	bool isAcyclic(GraphGenerator graph) {
            		if (graph.avlTreeRoot == NULL) {
                		return false;
            		}
            		Node *node  = graph.avlTreeRoot;
            		bool result = false;
            		isAcyclicChk(node, graph, &result);
            		return !isCyclic;
        	}

		// function that uses DFS to determine if it is a cyclic
		bool isAcyclic(int start, int num, GraphGenerator graph) {
		    	visitedDFS[start] = true;
            		llNode * curr = graph.getAdjList(start);
            		if (curr != NULL) {
                		curr = curr->next;
            		}

            		while(curr != NULL) {
		      		if (visitedDFS.find(curr->number) == visitedDFS.end()) {
		         		visitedDFS[curr->number] = true;
		         		isAcyclic(curr->number, start, graph);
		      		} else if (start != num && curr->number != num) {
		         		isCyclic = true;
		         		return true;
		      		}
		      		curr = curr->next;
		    	}
		}

		// function that uses BFS to print all connected components
		void connectedComponents(int start, GraphGenerator graph, Node * root) {

			//Find the connected component of the root argument vertice
			findConnectedComponents(start, graph, root);

			//Go through entire AVL tree to find all connected components
			Node * leftNode = root->leftChild;
			Node * rightNode = root->rightChild;
			if(leftNode != NULL) {
				connectedComponents(leftNode->number, graph, leftNode);
			}
			if(rightNode != NULL) {
				connectedComponents(rightNode->number, graph, rightNode);
			}

		}

		void findConnectedComponents(int start, GraphGenerator graph, Node * root){
			//create a list of connected vertices
			vector<int> queueAdj;
			int vectorBack;

            		vector<int> v;

			//if the starting vertice is already visited, no use in continuing as its connected component already found
			std::map<int, bool>::iterator it = visitedBFS.find(start);
			if (it == visitedBFS.end())
            		{
				//Found a new component, increment the 2d vector
				//bfsVectorCounter++;
				//If starting vertice not visited, mark it as visited and push the vertice onto vector
                		visitedBFS[start] = true;
				v.push_back(start);

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
                    			while(curr != NULL && curr->next)
                    			{

						//If a node hasn't been visited already, push it onto the queue, mark it visited, push it onto the vector

                        			std::map<int, bool>::iterator it = visitedBFS.find(curr->next->number);
                        			if(it == visitedBFS.end())
                        			{
                            				queueAdj.push_back(curr->next->number);
                            				visitedBFS[curr->next->number] = true;
                            				v.push_back(curr->next->number);
                        			}

                        		curr = curr->next;
                    			}
				}

                		std::sort(v.begin(), v.end());
                		for (int j=0; j< v.size(); j++){
                    			cout << v[j];
                    			cout << " ";
                		}
				cout << endl;
            		}
		}

};

#endif
