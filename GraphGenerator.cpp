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
		 // Node * avlTreeRoot =  new Node();


		int totalNumNodes = 0;
		
		//Constructs GraphGenerator object with input file
		GraphGenerator(string inputFile1)
		{	
			//insert into heaps
			string query = "";
			int data1 = 0;
			int data2 = 0;
			//cout << "INPUT FILE:" << inputFile1 << endl;
			ifstream insertFile(inputFile1);
			while(getline(insertFile, query))
			{
			//cout << "read input:" << query << endl;
				if(query.empty())
					break;
				int index = query.find(",");
				data1 = stoi(query.substr(0,index));
				//cout << "data1: " << data1 << endl;
				// << "data2:" << query.substr(index) << endl;
				data2 = stoi(query.substr(index+1));
				//cout << "data1:"<< data1 << ":data2: " << data2 << endl;
				bool insertedNode1 = insertVertex(data1);
				bool insertedNode2 = insertVertex(data2);
			    //if (insertedNode1 || insertedNode2) {
			        //cout << "insert edge: " << data1 << " :" << data2 << endl;
				    insertEdge(data1, data2);
				//}
			}
			insertFile.close();
		}
		// function that initializes a new pointer to a node
		Node * createNode(int data) {

			Node * node = new Node();

			node->number = data;
			node->leftChild = NULL;
			node->rightChild = NULL;
			node->height = 1;

            totalNumNodes++;

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
			root->height = max(getLeftHeight(root), getRightHeight(root)) + 1;
			newRoot->height = max(getLeftHeight(newRoot), getRightHeight(newRoot)) + 1;

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
			//root->height = max(root->leftChild->height, root->rightChild->height) + 1;
			root->height = max(getLeftHeight(root), getRightHeight(root)) + 1;

			newRoot->height = max(getLeftHeight(newRoot), getRightHeight(newRoot)) + 1;

			return newRoot;

		}

        int getLeftHeight(Node *node) {
            if (node->leftChild == NULL) return 0;
            return node->leftChild->height;
        }

                int getRightHeight(Node *node) {
                    if (node->rightChild == NULL) return 0;
                    return node->rightChild->height;
                }

		// function that checks if a node is balanced
		int getBalance(Node * node) {

			if(node == NULL) return 0;
			// positive means left is higher, negative means right is higher

			int balance = getLeftHeight(node) - getRightHeight(node);
			return balance;

		}

		// function that inserts a value into the tree
		Node * insert(Node * node, int data) {

			//cout << "insert1: " << node << ": data:" << data << endl;
			// create a new node as the leaf
			if(node == NULL) return createNode(data);

			//cout << "insert2: " << endl;

			// inserts to left side if value is less than the node value
			if(data < node->number) node->leftChild = insert(node->leftChild, data);
			// inserts to right side if value is less than then node value
			else if(data > node->number) node->rightChild = insert(node->rightChild, data);
			// cannot have duplicate values in the tree so it exits
			else return node;

			//cout << "insert3: " << endl;

			// update the new height for the root node
			int leftHeight = (node->leftChild? node->leftChild->height : 0);
			int rightHeight = (node->rightChild? node->rightChild->height: 0);
			node->height = max(leftHeight, rightHeight) + 1;

			//4: " << endl;

			// check the balance of the current node
			int balance = getBalance(node);
			//cout << "insert5: " << endl;

			// rotate the tree based on the balance
			if(balance > 1 && data < node->leftChild->number) {
			//cout << "insert8: " << endl;
			    return rotateRight(node);
			}
			else if(balance < - 1 && data > node->rightChild->number) {
			//cout << "insert9: " << endl;
			return rotateLeft(node);
			}
			else if(balance > 1 && data > node->leftChild->number) {
			//cout << "insert6: " << endl;
				node->leftChild = rotateLeft(node->leftChild);
				return rotateRight(node);

			} else if(balance < - 1 && data < node->rightChild->number) {
			//cout << "insert7: " << endl;
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

		}

		// function that inserts a llNode into a linked list
		void llInsert(llNode * start, int data) {

            	//cout << "llInsert: start:" << start << ": data:" << data << endl;
			llNode * current = start;

			while(current->next) {

				// if value already exists in the list
				if(current->number == data) return;

                current = current->next;
			}

            	//cout << "llInsert2" << endl;
			llNode * newLLNode = new llNode();
			newLLNode->number = data;

			current->next = newLLNode;

		}

		// function that checks if vertex exists and if not it inserts
			bool insertVertex(int data) {

			if (avlTreeRoot == NULL){
                		avlTreeRoot = createNode(data);
				return true;
            		}


			// lookup to see if the vertex already exists
			Node * searched = lookup(avlTreeRoot, data);


			// if it doesn't exist insert
			if(searched != NULL) {
			    return false;
			}

			avlTreeRoot = insert(avlTreeRoot, data);
			return true;
		}

		// function that inserts an edge into the adj list
		void insertEdge(int first, int second) {
            	//cout << "insertEdge: first:" << first << ":second:" << second << endl;

			// create two nodes to store vertices from lookup
			Node * firstVertex = lookup(avlTreeRoot, first);
			//"create firstVertex:" << firstVertex << endl;
			Node * secondVertex = lookup(avlTreeRoot, second);
			//cout << "create secondVertex: " << secondVertex << endl;

			// insert into the others adj list
			if (firstVertex->adjList == NULL){
			    firstVertex->adjList = new llNode();
			}
			if (secondVertex->adjList == NULL){
			    secondVertex->adjList = new llNode();
			}

			llInsert(firstVertex->adjList, second);
			llInsert(secondVertex->adjList, first);
			//cout << "Insert first for second vertex. " << endl;

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
