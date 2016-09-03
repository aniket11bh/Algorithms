/*
 * Author: Aniket Bhushan
 * Created: 21.08.2016
 *
 * CS29002, Assignment 3
 *
 * This file implements Binary search tree
 */

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

struct Node{
	int key;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};

int size(struct Node* tree)
{
	if(tree == NULL) return 0;

	return 1 + size(tree->left) + size(tree->right);
}

int height(struct Node* tree)
{
	if(tree == NULL) return -1;

	return 1 + max( height(tree->left), height(tree->right) );
}


void InorderTraverse(struct Node* node)
{
	if(node == NULL) return;

	InorderTraverse(node->left);
	cout << node->key << " ";
	InorderTraverse(node->right);
}

int SortBST(struct Node* node, int* sortedArray, int maxSize, int size)
{
	if(node == NULL) return size;

	size = SortBST(node->left, sortedArray, maxSize, size);

	sortedArray[size] = node->key;
	size++;

	size = SortBST(node->right, sortedArray, maxSize, size);
}

// create a new node with given key and return it's handle
struct Node* NewNode(int key)
{
	struct Node* temp = new(struct Node);
	temp->key = key;
	temp->left   = NULL;
	temp->right  = NULL;
	temp->parent = NULL;

	return temp;
}

struct Node* Insert(struct Node* node, int key)
{
	// Tree is Empty, return a new node
	if(node == NULL) return NewNode(key);

	// Otherwise get down to the correct location of key
	if(key > node->key )
	{
		node->right = Insert(node->right, key);
		node->right->parent = node;
	}

	else if(key < node->key)
	{
		node->left = Insert(node->left, key);
		node->left->parent = node;
	}

	return node;
}

struct Node* destroy(struct Node* root)
{
	if (root == NULL) return root;
	if (root->left == NULL && root->right == NULL){
		delete(root);
		root = NULL;
		return root;
	}
	root->left  = destroy(root->left);
	root->right = destroy(root->right);
	root = destroy(root);
	return root;
}

struct Node* CreateBalancedBST(struct Node* root, int* sortedArray, int size)
{
	int i;
	if(size <= 0)
		return NULL;
	else
		i = size/2;

	root = NewNode(sortedArray[i]);

	root->left  = CreateBalancedBST(root->left , sortedArray, i);
	if(root->left != NULL)  root->left->parent = root;

	root->right = CreateBalancedBST(root->right, sortedArray+i+1, size-i-1);
	if(root->right != NULL) root->right->parent = root;

	return root;
}

struct Node* Rebuild(struct Node* subtree, int size)
{
	int A[size];
	SortBST(subtree, A, size, 0);

	cout << "\n";
	subtree = destroy(subtree);
	subtree = CreateBalancedBST(subtree, A, size);
	// InorderTraverse(subtree);
	// cout << "\n Height : " << height(subtree) << "\n";
	return subtree;
}

// Insert the key a/c to BST insert, if the key is not present in the tree
struct Node* InsertKey(struct Node* tree, int key, int* m, int* n)
{
	struct Node* new_node = NewNode(key);
	int depth = 0;

	if(tree == NULL)
	{
		*n = *n + 1;
		if(*m < *n) *m = *n;
		return new_node;
	}
	struct Node* temp = tree;
	struct Node* tempParent = tree;

	while(temp != NULL)
	{
		tempParent = temp;
		if(key > temp->key)
		{
			temp = temp->right;
		}
		else if(key < temp->key)
		{
			temp = temp->left;
		}
		depth++;
	}

	if(key > tempParent->key)
		tempParent->right = new_node;
	else if(key < tempParent->key)
		tempParent->left = new_node;

	float constraint1 = 1 + log(*n)/log(1.5);

	if ((float)depth <= constraint1)
	{
		printf("Balanced : %d, %f \n",depth, constraint1);
	}
	else
	{
		printf("UnBalanced : %d, %f \n",depth, constraint1);
		int subtree_size = 1;
		int size_left = 0;
		int size_right = 0;
		struct Node* tempChild = tempParent;

		do
		{
			tempChild = tempParent;
			if(key > tempParent->key)
			{
				size_right = subtree_size;
				size_left = size(tempParent->left);
				subtree_size = 1 + size_left + size_right;
			}
			else if(key < tempParent->key)
			{
				size_left = subtree_size;
				size_right = size(tempParent->right);
				subtree_size = 1 + size_left + size_right;
			}
			tempParent = tempParent->parent;
		}
		while(((float)size_left <= 0.667*(float)subtree_size) && ((float)size_right <= 0.667*(float)subtree_size));
		cout << subtree_size << "\n";
		tempChild = Rebuild(tempChild, subtree_size);
		InorderTraverse(tree);
	}
	return tree;
}

int main()
{

	struct Node* tree = NULL;
	int* p = new(int);
	int *a;
	int num_inps, key;

	cout << "num_inps : ";
	cin >> num_inps;

	// Read user input
	cout << "Enter the numbers : ";
	for(int i=0; i<num_inps; i++){
		cin >> key;
		tree = Insert(tree, key);
	}

	InorderTraverse(tree);
	cout << "\n";

	cout << "size : "<< size(tree) << " height : "<< height(tree) << "\n";

	// tree = Rebuild(tree, size(tree));
	// cout << "Height : " << height(tree) << "\n";

	int n = size(tree);
	int m = n;
	tree = InsertKey(tree, 74, &m, &n);
	// InorderTraverse(tree);
	// cout << "Height : " << height(tree) << "\n";

	return 0;
}
