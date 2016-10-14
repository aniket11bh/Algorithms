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

	subtree = destroy(subtree);
	subtree = CreateBalancedBST(subtree, A, size);

	return subtree;
}

// Insert the key a/c to BST insert, if the key is not present in the tree
struct Node* InsertKey(struct Node* tree, int key, int* m, int* n, int rebuildPrintFlag)
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

	// Traverse where key is to be inserted
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
		else if(key == temp->key)
		{
			temp = NULL;
		}
		depth++;
	}

	if(key > tempParent->key)
	{
		tempParent->right = new_node;
		tempParent->right->parent = tempParent;
		*n = *n + 1;
		if(*m < *n) *m = *n;
	}
	else if(key < tempParent->key)
	{
		tempParent->left = new_node;
		tempParent->left->parent = tempParent;
		*n = *n + 1;
		if(*m < *n) *m = *n;
	}

	float constraint1 = 1 + log(*n)/log(1.5);

	if ((float)depth <= constraint1)
	{
		// printf("Balanced : %d, %f ",depth, constraint1);
		// printf("\t");
	}
	else
	{
		// printf("UnBalanced : %d, %f ",depth, constraint1);
		int subtree_size = 1;
		int size_left = 0;
		int size_right = 0;
		int prev_key = 0;
		struct Node* tempChild = tempParent;

		do
		{
			tempChild = tempParent;

			// Move left up
			if(key > tempParent->key)
			{
				size_right = subtree_size;
				size_left = size(tempParent->left);
				subtree_size = 1 + size_left + size_right;
			}

			// Move right up
			else if(key < tempParent->key)
			{
				size_left = subtree_size;
				size_right = size(tempParent->right);
				subtree_size = 1 + size_left + size_right;
			}
			tempParent = tempParent->parent;
		}
		while(((float)size_left <= 0.667*(float)subtree_size) && ((float)size_right <= 0.667*(float)subtree_size));

		if (rebuildPrintFlag )	printf("[R %d]", subtree_size);

		prev_key = tempChild->key;
		tempChild = Rebuild(tempChild, subtree_size);

		// Join the rebuilded subtree with rest of the tree //
		// Join on right side
		if (prev_key > tempParent->key)
		{
			tempParent->right = tempChild;
			tempChild->parent = tempParent;
		}

		// Join on left side
		else if (prev_key < tempParent->key)
		{
			tempParent->left = tempChild;
			tempChild->parent = tempParent;
		}
	}
	return tree;
}

struct Node* Find(struct Node* node, int key)
{
	// Tree is Empty, return NULL
	if(node == NULL || node->key == key) return node;

	// Otherwise get down to the correct location of key
	if(key > node->key )
	{
		return Find(node->right, key);
	}

	else if(key < node->key)
	{
		return Find(node->left, key);
	}
}

struct Node* FindMin(struct Node* node)
{
	if(node == NULL) return NULL;

	if(node->left == NULL)
		return node;

	else
		FindMin(node->left);
}

struct Node* DeleteKey(struct Node* tree, int key, int* n, int* m, int rebuildPrintFlag)
{
	struct Node* temp = Find(tree, key);
	struct Node* tempReplace;

	if(temp == NULL) return tree;

	else
	{
		// If key is at leaf, simply delete the key
		if (temp->left == NULL && temp->right == NULL)
		{
			if (temp->parent == NULL)
				return NULL;
			else if (key < temp->parent->key)
				temp->parent->left = NULL;
			else if(key > temp->parent->key)
				temp->parent->right = NULL;

			delete(temp);
		}

		// If node containing the key contains exaclty one node
		else if(temp->left == NULL || temp->right == NULL)
		{

			if (temp->parent == NULL)
			{
				if (temp->right != NULL)
					tree = temp->right;

				else if (temp->left != NULL)
					tree = temp->left;
				tree->parent = NULL;
			}

			// If key is on right side of it's parent node
			else if (key > temp->parent->key)
			{
				if (temp->right != NULL)
				{
					temp->parent->right = temp->right;
					temp->right->parent = temp->parent;
				}
				else
				{
					temp->parent->right = temp->left;
					temp->left->parent  = temp->parent;

				}
			}

			// If key is on left side of it's parent node
			else if(key < temp->parent->key)
			{
				if (temp->right != NULL)
				{
					temp->parent->left = temp->right;
					temp->right->parent = temp->parent;
				}
				else
				{
					temp->parent->left = temp->left;
					temp->left->parent  = temp->parent;
				}
			}
			delete(temp);
		}

		// If node containing the key contains two nodes
		else if(temp->right != NULL && temp->left != NULL)
		{
			tempReplace = FindMin(temp->right);
			temp->key = tempReplace->key;

			if (tempReplace->parent->key == tempReplace->key)
				tempReplace->parent->right = NULL;
			else
				tempReplace->parent->left = NULL;
			delete(tempReplace);
		}

		*n = *n - 1;

		if (*n < 2.0/3.0*(*m))
		{
			if (rebuildPrintFlag )	printf("[R %d]", *n);
			tree = Rebuild(tree, *n);
			*m = *n;
		}

		return tree;
	}
}

int main()
{

	struct Node* tree = NULL;
	int* p = new(int);
	int *a;
	int num_inps, key;
	int n = size(tree);
	int m = n;

	cout << "num_inps : ";
	cin >> num_inps;

	// Read user input to enter in tree
	cout << "Enter the numbers to insert keys: ";
	for(int i=0; i<num_inps; i++){
		cin >> key;
		// tree = Insert(tree, key);
		tree = InsertKey(tree, key, &m, &n, 1);
		cout << " Height = " <<  height(tree) << ":  ";
		InorderTraverse(tree);
		cout << "\n";
	}

	cout << "\n";
	cout << "num_inps : ";
	cin >> num_inps;

	// Read user input delete a key
	cout << "Enter the numbers to delete keys: ";
	for(int i=0; i<num_inps; i++){
		cin >> key;
		tree = DeleteKey(tree, key, &m, &n, 1);
		cout << " Height = " <<  height(tree) << ":  ";
		InorderTraverse(tree);
		cout << "\n";
	}


	cout << "Enter nins : ";
	cin >> num_inps;

	for(int i=1; i<=num_inps; i++)
	{
		tree = InsertKey(tree, i, &m, &n, 0);
		if (i%100 == 0)
			cout << " Height after " << i << "iterations : "<<  height(tree) << "\n";
	}

	cout << "Enter nins : ";
	cin >> num_inps;

	for(int i=1; i<=num_inps; i++)
	{
		tree = DeleteKey(tree, i, &m, &n, 0);
		if (i%100 == 0)
			cout << " Height after " << i << "iterations : "<<  height(tree) << "\n";
	}

	return 0;
}
