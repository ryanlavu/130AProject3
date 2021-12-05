#include <vector>
#include <iostream>

using namespace std;

class GraphGenerator {

	public:

		// struct used to create the adj list linked list
		struct llNode {

			int number;
			llNode * next;

		}

		// struct used to create an AVL tree for the adj list
		struct Node {

			// data needed to create the adjacency list
			int number;
			llNode * adjList;

			// data needed to create and balance the AVL tree
			Node * leftChild;
			Node * rightChild;
			int height;

		}

		// function that initializes a new pointer to a node
		Node * createNode(int data) {

			Node * node = new Node();

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
			if(node == NULL) return newNode(data);

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
			else if(balance < - 1 && data > node->rightChild->number) return leftRotate(node);
			else if(balance > 1 && data > node->leftChild->number) {

				node->leftChild = rotateLeft(node->leftChild);
				return rightRotate(node);

			} else if(balance < - 1 && data < node->rightChild->number) {

				node->rightChild = rotateRight(node->rightChild);
				return leftRotate(node);

			}

			return node;

		}



}
