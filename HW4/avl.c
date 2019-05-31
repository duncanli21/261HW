#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"


/* Alocate and initialize AVL tree structure. */
struct AVLTree * newAVLTree()
{
	struct AVLTree *tree = (struct AVLTree *)malloc(sizeof(struct AVLTree));
	assert(tree != 0);
	
	initAVLTree(tree);
	return tree;
}

/* Initialize AVL tree structure. */
void initAVLTree(struct AVLTree *tree)
{
	tree->cnt = 0;
	tree->root = 0;

}

void _freeAVL(struct AVLnode *node)
{
	if (node != 0) {
		_freeAVL(node->left);
		_freeAVL(node->right);		
		free(node);
	}
}

/* Deallocate nodes in AVL tree. */
void clearAVLTree(struct AVLTree *tree)
{
	_freeAVL(tree->root);
	tree->root = 0;
	tree->cnt  = 0;
}

/* Deallocate nodes in AVL tree and deallocate the AVL tree structure. */
void deleteAVLTree(struct AVLTree *tree)
{
	clearAVLTree(tree);
	free(tree);
}


/* return height of current node */
int h(struct AVLnode *current)
{
	if (current == 0)
		return -1;
	return current->height;
}

/* set height for current node */
void setHeight (struct AVLnode * current)
{
	int lch = h(current->left);
	int rch = h(current->right);
	if (lch < rch)
		current->height = 1 + rch;
	else
		current->height = 1 + lch;
}


int height(struct AVLnode* node) 
{ 
    if (node==NULL) 
        return 0; 
    else
    { 
        /* compute the height of each subtree */
        int lheight = height(node->left); 
        int rheight = height(node->right); 
  
        /* use the larger one */
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
} 

/* return balance factor value */
int bf(struct AVLnode * current)
{
	return h(current->left) - h(current->right);
}

/* left-rotate subtree of current node */
struct AVLnode * rotateLeft(struct AVLnode * current)
{
	struct AVLnode * newtop = current->right;

    struct AVLnode* z = newtop->left; 

    newtop->left = current; 
    current->right = z; 

    newtop->height = height(newtop);  
    current->height = height(current); 
	return newtop;
}

/* right-rotate subtree of current node */
struct AVLnode * rotateRight(struct AVLnode * current)
{
	struct AVLnode * newtop = current->left;

    struct AVLnode* z = newtop->right; 

    newtop->right = current; 
    current->left = z; 

    newtop->height = height(newtop);  
    current->height = height(current); 

	return newtop;
}

/* balance subtree of current node */
struct AVLnode * _balance(struct AVLnode * root)
{
	int balance = bf(root);

	setHeight(root);



	if(balance > 1 && root->left->left != NULL)
    {
        return rotateRight(root);
    }

    if(balance < -1 && root->right->right != NULL)
    {
        return rotateLeft(root); 
    }

    if(balance > 1 && root->left->right != NULL)
    {

        root->left = rotateLeft(root->left); 
        return rotateRight(root); 
    }

    if (balance < -1 && root->right->left != NULL)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root); 
    }



	return root;
}


struct AVLnode* newnode(TYPE val)
{
    struct AVLnode* newnode = (struct AVLnode*)malloc(sizeof(struct AVLnode));
    
    newnode->height = 1;
    newnode->left = NULL;
    newnode->right = NULL; 
    newnode->val = val; 

    return newnode; 
}


/* add newValue to subtree of current node */
struct AVLnode * AVLnodeAdd(struct	AVLnode * current, TYPE val)
{
	if(current == 0)
    return newnode(val);


    if(val < current->val)
    {
        current->left = AVLnodeAdd(current->left, val);
    }
    else
    {
        current->right = AVLnodeAdd(current->right, val); 
    }  


	current = _balance(current); 


	return current; 

}

/* add val to AVL tree */
void addAVLTree(struct AVLTree *tree, TYPE val)
{
	tree->root = AVLnodeAdd(tree->root, val);	
	tree->cnt++;
}

/* determine if val is contained in the AVL tree */
int containsAVLTree(struct AVLTree *tree, TYPE val)
{
	struct AVLnode* cur = tree->root;

	while(cur != 0){
		if (EQ(cur->val, val))	
			return 1;
		else if (LT(val, cur->val))
			cur = cur->left;
		else
			cur = cur->right;
	}

	return 0; 
}

/* find leftmost value from subtree of current node */
TYPE _leftMost(struct AVLnode *cur)
{
	while(cur->left != 0)
		cur = cur->left;
	return cur->val;
}

/* remove leftmost node from subtree of current node */
struct AVLnode * _removeLeftmost(struct AVLnode * cur)
{
	struct AVLnode * temp;

	if(cur->left != 0){
		cur->left = _removeLeftmost(cur->left);
		return _balance(cur);
	}

	temp = cur->right;
	free(cur);
	return temp;
}

/* remove val from subtree of cur node */
struct AVLnode * _removeNode(struct AVLnode * cur, TYPE val)
{
	struct AVLnode * temp;

	if(EQ(val, cur->val)){
		if(cur->right != 0){
			cur->val = _leftMost(cur->right);
			cur->right = _removeLeftmost(cur->right);
			return _balance(cur);
		} else {
			temp = cur->left;
			free(cur);
			return temp;
		}
	} else if (LT(val, cur->val))
		cur->left = _removeNode(cur->left, val);
	else cur->right = _removeNode(cur->right, val);

	return _balance(cur);
}

/* remove val from AVL tree */
void removeAVLTree(struct AVLTree * tree, TYPE val)
{
	if(containsAVLTree(tree, val)){
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

/* remove val from AVL tree */
void removeAllAVLTree(struct AVLTree * tree, TYPE val)
{
	if(containsAVLTree(tree, val))
		tree->root = _removeAllNodes(tree, tree->root, val);
}


struct AVLnode * _removeAllNodes(struct AVLTree * tree, struct AVLnode * cur, TYPE val){
   struct AVLnode * temp = NULL;
   while(EQ(val, cur->val)){
      if(cur->right != 0){
         cur->val = _leftMost(cur->right);
         cur->right = _removeLeftmost(cur->right);
         tree->cnt--;
      } else {
         temp = cur->left;
         free(cur);
         tree->cnt--;
         cur = temp;
      }
   }
   if (cur){  
      if (LT(val, cur->val))
         cur->left = _removeAllNodes(tree,cur->left, val);
      else 
         cur->right = _removeAllNodes(tree,cur->right, val);
   }
   return _balance(cur);
  
}


