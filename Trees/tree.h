#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _BiTreeNode {
	void* data;

	struct _BiTreeNode* leftChild;
	struct _BiTreeNode* rightChild;
} BiTreeNode;

typedef struct {
	int size;

	BiTreeNode* root;

	// The compare function to support searching.
	int (*compare)(const void* key1, const void* key2);

	// destroy is the function used to deallocated data.
	// Use NULL for static allocation and free() for malloc, calloc, etc.
	void (*destroy)(void* data);
} BiTree;

#define biTreeGetSize(tree) ((tree)->size)
#define biTreeGetRoot(tree) ((tree)->root)
#define biTreeGetData(node) ((node)->data)
#define biTreeGetLeft(node) ((node)->leftChild)
#define biTreeGetRight(node) ((node)->rightChild)
#define biTreeIsEOB(node) ((node) == NULL)
#define biTreeIsLeaf(node) ((node)->leftChild == NULL && (node)->rightChild)

BiTree* biTreeCreate(void (*destroy)(void* data));
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
BiTree* biTreeCreate(void (*destroy)(void* data)) {
	BiTree* tree = malloc(sizeof(BiTree));

	tree->size = 0;
	tree->root = NULL;

	tree->compare = NULL;
	tree->destroy = destroy;

	return tree;
}

int biTreeAddLeft(BiTree* tree, BiTreeNode* node, void* data) {
	// Initialise new node.
	BiTreeNode* newNode = malloc(sizeof(BiTreeNode));

	if(newNode == NULL) {
		fprintf(stderr, "Allocation of tree node failed.\n");
		return -1;
	}

	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	// Insertion at root.
	if(node == NULL) {
		if(tree->size == 0) {
			tree->root = newNode;
			tree->root->data = data;
			++(tree->size);

			return 0;
		}

		// Attempting insertion at root of a non-empty tree.
		return -1;
	}

	// Left child already exists.
	if(node->leftChild != NULL) {
		return -1;
	}

	node->leftChild = newNode;
	newNode->data = data;
	++(tree->size);

	return 0;
}

int biTreeAddRight(BiTree* tree, BiTreeNode* node, void* data) {
	// Initialise new node.
	BiTreeNode* newNode = malloc(sizeof(BiTreeNode));
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if(newNode == NULL) {
		fprintf(stderr, "Allocation of tree node failed.\n");
		return -1;
	}
	// Insertion at root.
	if(node == NULL) {
		if(tree->size == 0) {
			tree->root = newNode;
			tree->root->data = data;
			++(tree->size);

			return 0;
		}

		return -1;
	}

	// Right child already exists.
	if(node->rightChild != NULL) {
		return -1;
	}

	node->rightChild = newNode;
	newNode->data = data;

	++(tree->size);
	return 0;
}

// Wrapper to add root node.
int biTreeAddRoot(BiTree* tree, void* data) {
	return biTreeAddLeft(tree, NULL, data);
}

BiTree* biTreeMerge(BiTree* leftSubtree, BiTree* rightSubtree, void* newRootData) {
	// Create the root for the merged tree.
	BiTree* mergedTree = biTreeCreate(leftSubtree->destroy);

	if(mergedTree == NULL) {
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
void biTreeDelSubtree(BiTree* tree, BiTreeNode* node) {
	if(node == NULL) {
		return;
	}

	// Postorder tree traversal.
	biTreeDelSubtree(tree, node->leftChild);
	biTreeDelSubtree(tree, node->rightChild);

	if(tree->destroy != NULL) {
		tree->destroy(node->data);
	}
	
	free(node);
	--(tree->size);
}

// Wrapper for deleting the left child subtree.
void biTreeDelLeft(BiTree* tree, BiTreeNode* node) {
	biTreeDelSubtree(tree, node->leftChild);
	node->leftChild = NULL;
}

// Wrapper for deleting the right child subtree.
void biTreeDelRight(BiTree* tree, BiTreeNode* node) {
	biTreeDelSubtree(tree, node->rightChild);
	node->rightChild = NULL;
}

// Wrapper for deleting the entire tree structure.
void biTreeDestroy(BiTree* tree) {
	biTreeDelSubtree(tree, tree->root);
	free(tree);
}

#endif
