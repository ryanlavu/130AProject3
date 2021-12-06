#include <iostream>
#include <map>

#include "GraphGenerator.cpp"

using namespace std;

class GraphOperator {

	public:

		map<int, bool> visitedDFS;
		map<int, bool> visitedBFS;

		// function that uses DFS to check for cycles
		bool isAcyclic(int start, GraphGenerator graph) {

			visited[start] = true;

			bool allVisited = true;
			llNode * curr = graph.getAdjList(start);
			
			while(curr->next) {
				if(visited.find(curr->next->number)) return true;
				if(!visited.find(curr->next->number)) return isAcyclic(curr->next->number, graph);

			}

		}

		// function that uses BFS to print all connected components
		void connectedComponents(int start) {



		}

}
