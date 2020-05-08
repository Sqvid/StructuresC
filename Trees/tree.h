#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _BiTreeNode{
	void* data;

	struct _BiTreeNode* leftChild;
	struct _BiTreeNode* rightChild;
} BiTreeNode;

typedef struct{
	int size;

	BiTreeNode* root;

	void (*destroyFunction)(void* data);
} BiTree;

#define getBiTreeSize(tree) ((tree)->size)
#define getBiTreeRoot(tree) (tree) ((tree)->root)
#define getBiTreeData(node) ((node)->data)
#define getBiTreeLeft(node) ((node)->leftChild)
#define getBiTreeRight(node) ((node)->rightChild)
#define isBiTreeEOB(node) ((node) == NULL)
#define isBiTreeLeaf(node) ((node)->leftChild == NULL && (node)->rightChild)

BiTree* biTreeCreate(void (*destroyFunction)(void* data));
int biTreeAddLeft(BiTree* tree, BiTreeNode* node, void* data);
int biTreeAddRight(BiTree* tree, BiTreeNode* node, void* data);
int biTreeAddRoot(BiTree* tree, void* data);
BiTree* biTreeMerge(BiTree* leftSubtree, BiTree* rightSubtree, void* newRootData);
void biTreeDelSubtree(BiTree* tree, BiTreeNode* node);
void biTreeDelLeft(BiTree* tree, BiTreeNode* node);
void biTreeDelRight(BiTree* tree, BiTreeNode* node);
void biTreeDestroy(BiTree* tree);


// Function definitions:

// Initialise new tree and return pointer to it.
BiTree* biTreeCreate(void (*destroyFunction)(void* data)){
	BiTree* tree = malloc(sizeof(BiTree));

	tree->size = 0;
	tree->root = NULL;

	// destroyFunction is the function used to deallocated data.
	// Use NULL for static allocation and free() for malloc, calloc, etc.
	tree->destroyFunction = destroyFunction;

	return tree;
}

int biTreeAddLeft(BiTree* tree, BiTreeNode* node, void* data){
	// Initialise new node.
	BiTreeNode* newNode = malloc(sizeof(BiTreeNode));
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if(newNode == NULL){
		fprintf(stderr, "Allocation of tree node failed.\n");
		return -1;
	}

	// Insertion at root.
	if(node == NULL){
		if(tree->size == 0){
			tree->root = newNode;
			tree->root->data = data;
			++(tree->size);

			return 0;
		}

		return -1;
	}

	// Left child already exists.
	if(node->leftChild != NULL){
		return -1;
	}

	node->leftChild = newNode;
	newNode->data = data;
	++(tree->size);

	return 0;
}

int biTreeAddRight(BiTree* tree, BiTreeNode* node, void* data){
	// Initialise new node.
	BiTreeNode* newNode = malloc(sizeof(BiTreeNode));
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if(newNode == NULL){
		fprintf(stderr, "Allocation of tree node failed.\n");
		return -1;
	}
	// Insertion at root.
	if(node == NULL){
		if(tree->size == 0){
			tree->root = newNode;
			tree->root->data = data;
			++(tree->size);

			return 0;
		}

		return -1;
	}

	// Right child already exists.
	if(node->rightChild != NULL){
		return -1;
	}

	node->rightChild = newNode;
	newNode->data = data;

	++(tree->size);
	return 0;
}

// Wrapper to add root node.
int biTreeAddRoot(BiTree* tree, void* data){
	return biTreeAddLeft(tree, NULL, data);
}

BiTree* biTreeMerge(BiTree* leftSubtree, BiTree* rightSubtree, void* newRootData){
	// Create the root for the merged tree.
	BiTree* mergedTree = biTreeCreate(leftSubtree->destroyFunction);

	if(mergedTree == NULL){
		fprintf(stderr, "Allocation of merged tree failed.\n");
	}

	biTreeAddRoot(mergedTree, newRootData);

	// Attach left and right subtrees.
	mergedTree->root->leftChild = leftSubtree->root;
	mergedTree->root->rightChild = rightSubtree->root;
	mergedTree->size += leftSubtree->size + rightSubtree->size;

	// Overwrite the individual left and right subtrees.
	free(leftSubtree);
	free(rightSubtree);

	return mergedTree;
}

// Recursive function to delete subtrees. Do not use directly.
void biTreeDelSubtree(BiTree* tree, BiTreeNode* node){
	if(node == NULL){
		return;
	}

	// Postorder tree traversal.
	biTreeDelSubtree(tree, node->leftChild);
	biTreeDelSubtree(tree, node->rightChild);

	if(tree->destroyFunction != NULL){
		tree->destroyFunction(node->data);
	}
	
	free(node);
	--(tree->size);
}

// Wrapper for deleting the left child subtree.
void biTreeDelLeft(BiTree* tree, BiTreeNode* node){
	biTreeDelSubtree(tree, node->leftChild);
	node->leftChild = NULL;
}

// Wrapper for deleting the right child subtree.
void biTreeDelRight(BiTree* tree, BiTreeNode* node){
	biTreeDelSubtree(tree, node->rightChild);
	node->rightChild = NULL;
}

// Wrapper for deleting the entire tree structure.
void biTreeDestroy(BiTree* tree){
	biTreeDelSubtree(tree, tree->root);
	free(tree);
}

#endif
