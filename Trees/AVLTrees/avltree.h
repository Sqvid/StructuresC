#include "../tree.h"

#define AVL_L_HEAVY   1
#define AVL_BALANCED  0
#define AVL_R_HEAVY  -1

typedef BiTree AVLTree;
typedef BiTreeNode AVLTreeNode;

typedef struct {
	void* data;
	int avlFactor;
	int hidden;
} AVLNodeData;

#define avlTreeGetData(node) (((AVLNodeData*)((node)->data))->data)
#define avlTreeGetFactor(node) (((AVLNodeData*)((node)->data))->avlFactor)


AVLTree* avlTreeCreate(void (*destroy)(void* data),
		int (*compare)(const void* key1, const void* key2)) {

	AVLTree* tree = malloc(sizeof(BiTree));

	tree->size = 0;
	tree->root = NULL;

	tree->compare = compare;
	tree->destroy = destroy;

	return tree;
}

// Left rotate helper function.
void _avlLeftRotate(AVLTreeNode** badNodePtr) {
	AVLTreeNode* left, *grandchild, *badNode;


	badNode = *badNodePtr;
	left = biTreeGetLeft(badNode);
	grandchild = biTreeGetRight(left);

	// LL-Rotation.
	if(avlTreeGetFactor(left) == AVL_L_HEAVY) {
		biTreeGetLeft(badNode) = biTreeGetRight(left);
		biTreeGetRight(left) = badNode;
		avlTreeGetFactor(left) = AVL_BALANCED;
		avlTreeGetFactor(badNode) = AVL_BALANCED;
		badNode = left;

	// LR-Rotation.
	} else {
		biTreeGetRight(left) = biTreeGetLeft(grandchild);
		biTreeGetLeft(grandchild) = left;
		biTreeGetLeft(badNode) = biTreeGetRight(grandchild);
		biTreeGetRight(grandchild) = badNode;
		badNode = grandchild;

		//Update balance factors.
		switch(avlTreeGetFactor(grandchild)) {
			case AVL_L_HEAVY:
				avlTreeGetFactor(biTreeGetLeft(badNode)) = AVL_BALANCED;
				avlTreeGetFactor(biTreeGetRight(badNode)) = AVL_R_HEAVY;
				break;
			case AVL_BALANCED:
				avlTreeGetFactor(biTreeGetLeft(badNode)) = AVL_BALANCED;
				avlTreeGetFactor(biTreeGetRight(badNode)) = AVL_BALANCED;
				break;
			case AVL_R_HEAVY:
				avlTreeGetFactor(biTreeGetLeft(badNode)) = AVL_L_HEAVY;
				avlTreeGetFactor(biTreeGetRight(badNode)) = AVL_BALANCED;
				break;
		}

		avlTreeGetFactor(badNode) = 0;
	}
}

// Right rotate helper function.
void _avlRightRotate(AVLTreeNode** badNodePtr) {
	AVLTreeNode* right, *grandchild, *badNode;


	badNode = *badNodePtr;
	right = biTreeGetRight(badNode);
	grandchild = biTreeGetLeft(right);

	// RR-Rotation.
	if(avlTreeGetFactor(right) == AVL_R_HEAVY) {
		biTreeGetRight(badNode) = biTreeGetLeft(right);
		biTreeGetLeft(right) = badNode;
		avlTreeGetFactor(right) = AVL_BALANCED;
		avlTreeGetFactor(badNode) = AVL_BALANCED;
		badNode = right;

	// RL-Rotation.
	} else {
		biTreeGetLeft(right) = biTreeGetRight(grandchild);
		biTreeGetRight(grandchild) = right;
		biTreeGetRight(badNode) = biTreeGetLeft(grandchild);
		biTreeGetLeft(grandchild) = badNode;
		badNode = grandchild;

		//Update balance factors.
		switch(avlTreeGetFactor(grandchild)) {
			case AVL_L_HEAVY:
				avlTreeGetFactor(biTreeGetLeft(badNode)) = AVL_BALANCED;
				avlTreeGetFactor(biTreeGetRight(badNode)) = AVL_R_HEAVY;
				break;
			case AVL_BALANCED:
				avlTreeGetFactor(biTreeGetLeft(badNode)) = AVL_BALANCED;
				avlTreeGetFactor(biTreeGetRight(badNode)) = AVL_BALANCED;
				break;
			case AVL_R_HEAVY:
				avlTreeGetFactor(biTreeGetLeft(badNode)) = AVL_L_HEAVY;
				avlTreeGetFactor(biTreeGetRight(badNode)) = AVL_BALANCED;
				break;
		}

		avlTreeGetFactor(badNode) = 0;
	}
}

int avlTreeInsert(AVLTree* tree, AVLTreeNode* node) {
	AVLNodeData* avldata = malloc(sizeof(AVLNodeData));
	avldata->data = node->data;
	node->data = avldata;

	/* insert helper */


}<++>

int _avlInsert(AVLTree* tree, AVLTreeNode* currentNode, AVLTreeNode* node) {
	if(tree->compare(currentNode, node) == 0) {
		return -1;
	} else if(biTreeIsEOB(currentNode) == 1) {
		
	}<++>
}<++>
