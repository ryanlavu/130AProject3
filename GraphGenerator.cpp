#ifndef GRAPHG
#define GRAPHG

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

	// struct used to create the adj list linked list
	struct llNode {

		int number;
		llNode * next;

	};

	// struct used to create an AVL tree for the adj list
	struct Node {

		// data needed to create the adjacency list
		int number;
		llNode * adjList;

		// data needed to create and balance the AVL tree
		Node * leftChild;
		Node * rightChild;
		int height;

	};

class GraphGenerator {

	public:
		Node * avlTreeRoot = NULL;
		
		//Constructs GraphGenerator object with input file
		GraphGenerator(string inputFile1)
		{	
			//insert into heaps
			string query = "";
			int data1 = 0;
			int data2 = 0;
			ifstream insertFile(inputFile1);
			while(getline(insertFile, query))
			{
				if(query.empty())
					break;
				cout << query << endl;
				cout << query.substr(0,query.find(",")) << endl;
				cout << query.substr(query.find(",") + 1) << endl; 
				data1 = stoi(query.substr(0,query.find(",")));
				data2 = stoi(query.substr(query.find(",") + 1));
				insertVertex(data1);
				insertVertex(data2);
				insertEdge(data1, data2);
			}
			insertFile.close();
		}
		// function that initializes a new pointer to a node
		Node * createNode(int data) {

			Node * node = new Node();

			node->adjList == NULL;
			
			node->number = data;
			node->leftChild = NULL;
			node->rightChild = NULL;
			node->height = 1;

			return node;

		}

		// function that rotates a tree right based on a given root
		Node * rotateRight(Node * root) {

			// find new root and child that will be moved
			Node * newRoot = root->leftChild;
			Node * nrRightTree = newRoot->rightChild;

			// rotates the tree
			newRoot->rightChild = root;
			root->leftChild = nrRightTree;

			// fix the heights for new tree
			root->height = max(root->leftChild->height, root->rightChild->height) + 1;
			newRoot->height = max(newRoot->leftChild->height, newRoot->rightChild->height) + 1;

			return newRoot;

		}

		// function that rotates a tree left based on a given root
		Node * rotateLeft(Node * root) {

			// find new root and child that will be moved
			Node * newRoot = root->rightChild;
			Node * nrLeftTree = newRoot->leftChild;

			// rotates the tree
			newRoot->leftChild = root;
			root->rightChild = nrLeftTree;

			// fix the heights for new tree
			root->height = max(root->leftChild->height, root->rightChild->height) + 1;
			newRoot->height = max(newRoot->leftChild->height, newRoot->rightChild->height) + 1;

			return newRoot;

		}

		// function that checks if a node is balanced
		int getBalance(Node * node) {

			if(node == NULL) return 0;
			// positive means left is higher, negative means right is higher
			int balance = node->leftChild->height - node->rightChild->height;
			return balance;

		}

		// function that inserts a value into the tree
		Node * insert(Node * node, int data) {

			// create a new node as the leaf
			if(node == NULL) return createNode(data);

			// inserts to left side if value is less than the node value
			if(data < node->number) node->leftChild = insert(node->leftChild, data);
			// inserts to right side if value is less than then node value
			else if(data > node->number) node->rightChild = insert(node->rightChild, data);
			// cannot have duplicate values in the tree so it exits
			else return node;

			// update the new height for the root node
			node->height = max(node->leftChild->height, node->rightChild->height) + 1;

			// check the balance of the current node
			int balance = getBalance(node);

			// rotate the tree based on the balance
			if(balance > 1 && data < node->leftChild->number) return rotateRight(node);
			else if(balance < - 1 && data > node->rightChild->number) return rotateLeft(node);
			else if(balance > 1 && data > node->leftChild->number) {

				node->leftChild = rotateLeft(node->leftChild);
				return rotateRight(node);

			} else if(balance < - 1 && data < node->rightChild->number) {

				node->rightChild = rotateRight(node->rightChild);
				return rotateLeft(node);

			}

			return node;

		}

		// function that finds a node in the tree
		Node * lookup(Node * node, int data) {

			// base cases for if the value is found or not
			if(node == NULL) return NULL;
			else if(node->number == data) return node;

			// goes to the correct child depending on data comparison
			if(data < node->number) return lookup(node->leftChild, data);
			else if(data > node->number) return lookup(node->rightChild, data);
			
			return NULL;

		}
	
		llNode * createLLNodeHead(int data) {
		
			llNode * node = new llNode();
			
			node->number = data;
			
			return node;
			
		}

		// function that inserts a llNode into a linked list
		void llInsert(llNode * start, int data) {

			if(start == NULL) {
				
				llNode * temp = createLLNodeHead(data);
				start = temp;
				
			}
			
			llNode * current = start;

			while(current->next) {

				// if value already exists in the list
				if(current->number == data) return;

			}

			llNode * newLLNode = new llNode();
			newLLNode->number = data;

			current->next = newLLNode;

		}

		// function that checks if vertex exists and if not it inserts
		void insertVertex(int data) {
			
			// lookup to see if the vertex already exists
			Node * searched = lookup(avlTreeRoot, data);

			// if it doesn't exist insert
			if(searched == NULL) avlTreeRoot = insert(avlTreeRoot, data);

		}

		// function that inserts an edge into the adj list
		void insertEdge(int first, int second) {

			cout << "before insert edge" << endl;
			
			// create two nodes to store vertices from lookup
			Node * firstVertex = lookup(avlTreeRoot, first);
			Node * secondVertex = lookup(avlTreeRoot, second);

			cout << "before llInsert" << endl;
			
			// insert into the others adj list
			llInsert(firstVertex->adjList, second);
			llInsert(secondVertex->adjList, first);

		}

		// print the AVL tree "in order"
		void inOrder(Node * node) {

			// base case when it reaches a leaf
			if(node == NULL) return;

			// inorder prints left -> root -> right
			inOrder(node->leftChild);
			cout << node->number << " ";
			inOrder(node->rightChild);

		}

		// print the AVL tree "pre order"
		void preOrder(Node * node) {

			// base case when it reaches a leaf
			if(node == NULL) return;

			// prints the value of the node
			cout << node->number << " ";

			// preorder prints left before right
			preOrder(node->leftChild);
			preOrder(node->rightChild);

		}

		// function that returns the adj list from data
		llNode * getAdjList(int data) {

			return lookup(avlTreeRoot, data)->adjList;

		}

};

#endif
