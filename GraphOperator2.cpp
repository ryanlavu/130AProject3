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
		//TODO
		map<int, bool> visitedAdjList;
		
		vector<vector<int>>  vectorBFS; 
		int bfsVectorCounter = 0;

		// function that uses DFS to check for cycles
		
	void isAcyclicChk(Node *node, GraphGenerator graph, bool *result){
            if(node == NULL || *result) return;

            //cout << "---- in ascyclic : " << node->number << " start." << endl;
            *result = isAcyclic(node->number, node->number, graph);
            //cout << "---- in ascyclic : " << node->number << " sttar2:" << *result << "." << endl;

            if(*result || isCyclic) return;

            // cout << "---- in ascyclic : " << node->number << " START LET CHILD:" << node->leftChild << "." << endl;
            isAcyclicChk(node->leftChild, graph, result);

            if (*result|| isCyclic) return;

           // cout << "---- in ascyclic : " << node->number << " START RIGHT CHILD:" << node->rightChild << "." << endl;
            isAcyclicChk(node->rightChild, graph, result);

		}

				
	bool isAcyclic(GraphGenerator graph) {
		if (graph.avlTreeRoot == NULL) {
        		return false;
		}

        	Node *node  = graph.avlTreeRoot;
        	bool result = false;
        	isAcyclicChk(node, graph, &result);
      		//isAcyclic(node->number, node->number, graph);

        	return !isCyclic;
        }

        bool isCyclic = false;

	bool isAcyclic(int start, int num, GraphGenerator graph) {
		//cout << "isAcyclic, start:" << start << ", num:" << num << endl;
		visitedDFS[start] = true;
            	llNode * curr = graph.getAdjList(start);
            	if (curr != NULL) {
                	curr = curr->next;
            	}

            	while(curr != NULL) {
                	//cout << "checking : start: " << start << ":num:" << num << ":" << ":inloop:" << curr->number << endl;
			if (visitedDFS.find(curr->number) == visitedDFS.end()) {
				visitedDFS[curr->number] = true;
		        	isAcyclic(curr->number, start, graph);
			} 
			else if (start != num && curr->number != num) {
				isCyclic = true;
		        	return true;
			}
		      	curr = curr->next;
		}
	}

	// function that uses BFS to print all connected components
	void connectedComponents(int start, GraphGenerator graph, Node * root) {

		cout << "connectedComponents: start: " << start << "root: " << root << endl;

		//Find the connected component of the root argument vertice
		findConnectedComponents(start, graph, root);
			
		//Go through entire AVL tree to find all connected components
		Node * leftNode = root->leftChild;
		Node * rightNode = root->rightChild;
		if(leftNode != NULL) {
			// cout << "call LEFT  again: " << leftNode->number;
			connectedComponents(leftNode->number, graph, leftNode);
		}
		if(rightNode != NULL) {
			//cout << "call RIGHT again: " << leftNode->number;
			connectedComponents(rightNode->number, graph, rightNode);
		}

	}

		

	void findConnectedComponents(int start, GraphGenerator graph, Node * root){
		cout << "findConnectedComponents: " << start << ":root" << root << endl;
		//create a list of connected vertices
		vector<int> queueAdj;
		int vectorBack;

		//if the starting vertice is already visited, no use in continuing as its connected component already found
		//if (!visitedBFS.find(start))
		std::map<int, bool>::iterator it = visitedBFS.find(start);
		//if(it == visitedBFS.end() && !it->second)
		if (it == visitedBFS.end())
            	{
			//Found a new component, increment the 2d vector
			bfsVectorCounter++;

			//If starting vertice not visited, mark it as visited and push the vertice onto vector
                	visitedBFS[start] = true;
                	vector<int> v;

			v.push_back(start);
			vectorBFS.push_back(v);

			//let the current vertice be pushed onto queueAdj
			llNode * curr;
			queueAdj.push_back(start);

			//only stop looking when no more connected vertices left
			while(!queueAdj.empty())
			{
				cout << "test" << endl;
				//let the current vertice be grabbed from queueAdj
				vectorBack = queueAdj.back();
				curr = graph.getAdjList(vectorBack);

				queueAdj.pop_back();

				//only stop looking at adjacent vertices of the current vertice when there are no more

                                while(curr->next != NULL)
                                {
					//If a node hasn't been visited already, push it onto the queue, mark it visited, push it onto the vector

                                        //if(!visitedBFS.find(curr->next->number))
					cout << "before!" << endl;
                                        std::map<int, bool>::iterator it = visitedDFS.find(curr->next->number);
					cout << "after!" << endl;
                                        if(it != visitedBFS.end() && !it->second)
                                       	{
                                        	cout << "find in whileloop3: " <<  curr->next->number << endl;
                                                queueAdj.push_back(curr->next->number);
                                                visitedBFS[curr->next->number] = true;
						v.push_back(curr->next->number);
                                        }
					//cout << "after if!" << endl;
                                        curr = curr->next;
					cout << "AFTER" << endl;
                                }
			}

			//Sort and print out the vector
			std::sort(vectorBFS[bfsVectorCounter].begin(), vectorBFS[bfsVectorCounter].end());
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
