#ifndef TREE_H
#define TREE_H

typedef struct treeNode {
    int userID;
    deList* children;
    ssList* movies;
    delNode* parent;
} treeNode;

typedef struct treeTree {
	treeNode* node;
	treeNode** users;
} treeTree;

treeTree* treeSetTree ();

bool treeAddNode (treeTree* t, int parent_id, int id);

void treePrintTree (treeTree* t, int root_id);

bool treeDeleteNode (treeTree* t, int id);
void treeDeleteTree (treeTree* t);

#endif /* TREE_H */
