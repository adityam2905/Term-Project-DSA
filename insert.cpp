#include <bits/stdc++.h>

Node* insertAVL(Node* root, int value)
{
    if (root == NULL){
        return createAVL(value);
		}
    if (value < root->value){
        root->left = insertAVL(root->left, value);
    }
    else if (value > root->value){
        root->right = insertAVL(root->right, value);
    }
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && value < root->left->value){
        return rightRotate(root);
    }
    if (balance < -1 && value > root->right->value) return leftRotate(root);
    
    if (balance > 1 && value > root->left->value) return leftRightRotate(root);
    if (balance < -1 && value < root->right->value) return rightLeftRotate(root);
	return root;
}

void modifyCGPA(int rollNo1,int newcgpa){
	Node* node=AVLsearch(root,rollno1);
	node->cgpa= newcgpa;
	return;
}

void printLesserThanCGPA(Node* node , float cg){
   if(root==NULL) return;
   if(node->cgpa < cg){
   	
      cout<<node->name<<endl;
      cout<<node->cgpa<<endl;
      cout<<node->rollNo<<endl;
      printLesserThanCGPA(node->right , cgpa);
   }
      printLesserThanCGPA(node->left, cgpa);
}
void printGreaterThanCGPA(Node* node , float cg){
   if(root==NULL) return;
   
   if(node->cgpa > cg){
      cout<<node->name<<endl;
      cout<<node->rollNo<<endl;
      cout<<node->cgpa<<endl;
      printGreaterThanCGPA(node->left , cgpa);
   }
      printGreaterThanCGPA(node->right, cgpa);
}
void printInBetweenCGPA(Node* node , float cg1 , float cg2){
     if(root==NULL) return;
     if(cg1 < node->cgpa){
         printInBetweenCGPA(node->left , cg1 , cg2);
     }
     else if(cg2 > node->cgpa){
         printInBetweenCGPA(node->right , cg1 , cg2);
     }
     else if(cg1 > node->cgpa && cg2 < node->cgpa){
      cout<<node->name<<endl;
      cout<<node->rollNo<<endl;
      cout<<node->cgpa<<endl;
     }
 }

