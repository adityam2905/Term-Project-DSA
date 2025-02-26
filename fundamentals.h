#ifndef AVLTREE_H
#define AVLTREE_H

#include <bits/stdc++.h>
#include "node.h"
using namespace std;

void Updateheight(Node* root);
Node* LLR(Node* root);
Node* RRR(Node* root);
Node* LRR(Node* root);
Node* RLR(Node* root);
Node* search(Node* root, int key);

#endif

