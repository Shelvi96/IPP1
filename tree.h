#ifndef TREE_H
#define TREE_H

typedef struct treeNode {
    int userID;
    deList* children;
    ssList* movies;
    delNode* parent;
    deList* parentArr;
} treeNode;

typedef struct treeTree {
	treeNode* node;
	treeNode** users;
} treeTree;

treeTree* treeSetTree ();

void treeAddNode (treeTree* t, int id, int parentid);

void treePrintTree (treeTree* t, int root_id);

void treeDeleteNode (treeTree* t, int id);
void treeDeleteTree (treeTree* t);

#endif /* TREE_H */
