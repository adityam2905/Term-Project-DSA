#include <bits/stdc++.h>
#include "fundamentals.h"
void Updateheight(struct Node* root){
    if (root != NULL){
        int val = 1;
        if (root->left != NULL)
            val = root->left->height + 1;

        if (root->right != NULL)
            val = max(val, root->right->height + 1);
        root->height = val;
    }
}

struct Node* LLR(struct Node* root)
{
    struct Node* tmpnode = root->left;
    root->left = tmpnode->right;

   
    if (tmpnode->right != NULL)
        tmpnode->right->par = root;

    tmpnode->right = root;

    tmpnode->par = root->par;

    root->par = tmpnode;

    if (tmpnode->par != NULL
        && root->key < tmpnode->par->key) {
        tmpnode->par->left = tmpnode;
    }
    else {
        if (tmpnode->par != NULL)
            tmpnode->par->right = tmpnode;
    }

    root = tmpnode;

    Updateheight(root->left);
    Updateheight(root->right);
    Updateheight(root);
    Updateheight(root->par);

    return root;
}
struct Node* RRR(struct Node* root){
    struct Node* tmpnode = root->right;
    root->right = tmpnode->left;

    if (tmpnode->left != NULL)
        tmpnode->left->par = root;

    tmpnode->left = root;

 
    tmpnode->par = root->par;

    root->par = tmpnode;

    if (tmpnode->par != NULL && root->key < tmpnode->par->key) {
        tmpnode->par->left = tmpnode;
    }
    else {
	   if (tmpnode->par != NULL) tmpnode->par->right = tmpnode;
    }
    
    root = tmpnode;

    Updateheight(root->left);
    Updateheight(root->right);
    Updateheight(root);
    Updateheight(root->par);

    return root;
}

struct Node* LRR(struct Node* root){
    root->left = RRR(root->left);
    return LLR(root);
}

struct Node* RLR(struct Node* root){
    root->right = LLR(root->right);
    return RRR(root);
}

Node* search(struct Node* root, int key){

    if (root == NULL)
        return false;


    else if (root->key == key)
        return root;


    else if (root->key > key) {
        Node* node = AVLsearch(root->left, key);
        return node;
    }

   
    else {
        Node* node = AVLsearch(root->right, key);
        return node;
    }
}
