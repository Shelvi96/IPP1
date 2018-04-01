#ifndef TREE_H
#define TREE_H

typedef struct treeNode {
    int userID;
    deList* children;
    ssList* movies;
} treeNode;

typedef struct treeTree {
	treeNode* node;
	treeNode** users;
} treeTree;

treeTree* treeSetTree ();
void treeAddNode (treeTree* t, int id, int parentid);

void treePrintTree (treeTree* t, int root_id);

// void treePrintArr (int x);
// void treeDeleteTree (treeTree* t);

#endif /* TREE_H */