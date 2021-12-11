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
		vector<vector<int>> vectorBFS;
        bool isAcyclicGraph = true;

    void chkAcyclic(Node *node, GraphGenerator graph, bool *result){
        if(node == NULL || !*result) return;

        isAcyclic(node->number, node->number, graph);
        if(!isAcyclicGraph) return;

        chkAcyclic(node->leftChild, graph, result);
        if (!isAcyclicGraph) return;

        chkAcyclic(node->rightChild, graph, result);
	}

				
	bool isAcyclic(GraphGenerator graph) {
            	if (graph.avlTreeRoot == NULL) {
                	return true;
            	}
            	Node *node  = graph.avlTreeRoot;
            	bool result = true;
            	chkAcyclic(node, graph, &result);
            	return isAcyclicGraph;
        }

	// function that uses DFS to determine if it is a cyclic
	// Checks whether the graph is acyclic or not
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
            }
            else if (start != num && curr->number != num) {
                isAcyclicGraph = false;
                return false;
            }
            curr = curr->next;
		}
	}


	// function that uses BFS to print all connected components
	// Find and print all of the connected components of the graph
	void connectedComponents(int start, GraphGenerator graph) {
		vectorBFS.clear();
		Node *root = graph.avlTreeRoot;
        connectedComponents2(start, graph, root);

        for (int i=0; i< vectorBFS.size(); i++){
            std::sort(vectorBFS[i].begin(), vectorBFS[i].end());
        }

        std::sort(vectorBFS.begin(), vectorBFS.end(),
        [](const vector<int> & a, const vector<int> & b){
                return a[0] < b[0]; });
        for (int i=0; i < vectorBFS.size(); i++){
            vector<int> v = vectorBFS[i];
            for (int j=0; j< v.size(); j++){
                    cout << v[j];
                    cout << " ";
            }
            cout << endl;
        }
	}

    void connectedComponents2(int start, GraphGenerator graph, Node * root) {
        //Find the connected component of the root argument
        findConnectedComponents(start, graph, root);

        //Go through entire AVL tree to find all connected components
        Node * leftNode = root->leftChild;
        Node * rightNode = root->rightChild;
        if(leftNode != NULL) {
            connectedComponents2(leftNode->number, graph, leftNode);
        }
        if(rightNode != NULL) {
            connectedComponents2(rightNode->number, graph, rightNode);
        }
    }


    static bool sortNode( const vector<int>& v1, const vector<int>& v2 ) {
    return v1[0] < v2[0];
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

            vectorBFS.push_back(v);
        }
	}

};

#endif
